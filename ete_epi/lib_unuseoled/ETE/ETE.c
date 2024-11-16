/*
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)
Copyright 2023 kushima8
Copyright 2023 YMGWorks

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "quantum.h"
#ifdef SPLIT_KEYBOARD
#    include "transactions.h"
#endif

#include <limits.h>

#include "host.h"
#include "keycode.h"
#include "keyboard.h"
#include "mousekey.h"
#include "programmable_button.h"
#include "command.h"
#include "led.h"
#include "action_layer.h"
#include "action_tapping.h"
#include "action_util.h"
#include "action.h"
#include "wait.h"
#include "keycode_config.h"
#include "debug.h"
#include "quantum.h"

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif

#ifdef POINTING_DEVICE_ENABLE
#    include "pointing_device.h"
#endif

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE) && defined(SWAP_HANDS_ENABLE)
#    include "encoder.h"
#endif



#include "ETE.h"
#include "drivers/pmw3360/pmw3360.h"

const uint8_t CPI_DEFAULT    = ETE_CPI_DEFAULT / 100;
const uint8_t CPI_MAX        = pmw3360_MAXCPI + 1;
const uint8_t SCROLL_DIV_MAX = 7;

ETE_t ETE = {
    .this_have_ball = false,
    .that_enable    = false,
    .that_have_ball = false,

    .this_motion = {0},
    .that_motion = {0},

    .cpi_value   = 0,
    .cpi_changed = false,

    .scroll_mode = false,
    .scroll_div  = 0,
};

//////////////////////////////////////////////////////////////////////////////
// Hook points

__attribute__((weak)) void ETE_on_adjust_layout(ETE_adjust_t v) {}

//////////////////////////////////////////////////////////////////////////////
// Static utilities

// add16 adds two int16_t with clipping.
static int16_t add16(int16_t a, int16_t b) {
    int16_t r = a + b;
    if (a >= 0 && b >= 0 && r < 0) {
        r = 32767;
    } else if (a < 0 && b < 0 && r >= 0) {
        r = -32768;
    }
    return r;
}

// clip2int8 clips an integer fit into int8_t.
static inline int8_t clip2int8(int16_t v) {
    return (v) < -127 ? -127 : (v) > 127 ? 127 : (int8_t)v;
}



static void add_cpi(int8_t delta) {
    int16_t v = ETE_get_cpi() + delta;
    ETE_set_cpi(v < 1 ? 1 : v);
}

static void add_scroll_div(int8_t delta) {
    int8_t v = ETE_get_scroll_div() + delta;
    ETE_set_scroll_div(v < 1 ? 1 : v);
}

//////////////////////////////////////////////////////////////////////////////
// Pointing device driver

void pointing_device_driver_init(void) {
    ETE.this_have_ball = pmw3360_init();
    if (ETE.this_have_ball) {
        pmw3360_cpi_set(CPI_DEFAULT - 1);
        pmw3360_reg_write(pmw3360_Motion_Burst, 0);
    }
}

uint16_t pointing_device_driver_get_cpi(void) {
    return ETE_get_cpi();
}

void pointing_device_driver_set_cpi(uint16_t cpi) {
    ETE_set_cpi(cpi);
}

static void motion_to_mouse_move(ETE_motion_t *m, report_mouse_t *r, bool is_left) {
    r->x = -clip2int8(m->x);
    r->y = clip2int8(m->y);
    // clear motion
    m->x = 0;
    m->y = 0;
}

static void motion_to_mouse_scroll(ETE_motion_t *m, report_mouse_t *r, bool is_left) {
    // consume motion of trackball.
    uint8_t div = ETE_get_scroll_div() - 1;
    int16_t x   = m->x >> div;
    m->x -= x << div;
    int16_t y = m->y >> div;
    m->y -= y << div;

    // apply to mouse report.
    r->h = clip2int8(x);
    r->v = clip2int8(y);

#if ETE_SCROLLSNAP_ENABLE
    // scroll snap.
    uint32_t now = timer_read32();
    if (r->h != 0 || r->v != 0) {
        ETE.scroll_snap_last = now;
    } else if (TIMER_DIFF_32(now, ETE.scroll_snap_last) >= ETE_SCROLLSNAP_RESET_TIMER) {
        ETE.scroll_snap_tension_h = 0;
    }
    if (abs(ETE.scroll_snap_tension_h) < ETE_SCROLLSNAP_TENSION_THRESHOLD) {
        ETE.scroll_snap_tension_h += y;
        r->h = 0;
    }
#endif
}

static void motion_to_mouse(ETE_motion_t *m, report_mouse_t *r, bool is_left, bool as_scroll) {
    if (as_scroll) {
        motion_to_mouse_scroll(m, r, is_left);
    } else {
        motion_to_mouse_move(m, r, is_left);
    }
}

static inline bool should_report(void) {
    uint32_t now = timer_read32();
#if defined(ETE_REPORTMOUSE_INTERVAL) && ETE_REPORTMOUSE_INTERVAL > 0
    // throttling mouse report rate.
    static uint32_t last = 0;
    if (TIMER_DIFF_32(now, last) < ETE_REPORTMOUSE_INTERVAL) {
        return false;
    }
    last = now;
#endif
#if defined(ETE_SCROLLBALL_INHIVITOR) && ETE_SCROLLBALL_INHIVITOR > 0
    if (TIMER_DIFF_32(now, ETE.scroll_mode_changed) < ETE_SCROLLBALL_INHIVITOR) {
        ETE.this_motion.x = 0;
        ETE.this_motion.y = 0;
        ETE.that_motion.x = 0;
        ETE.that_motion.y = 0;
    }
#endif
    return true;
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t rep) {
    // fetch from optical sensor.
    if (ETE.this_have_ball) {
        pmw3360_motion_t d = {0};
        if (pmw3360_motion_burst(&d)) {
            ATOMIC_BLOCK_FORCEON {
                ETE.this_motion.x = add16(ETE.this_motion.x, d.x);
                ETE.this_motion.y = add16(ETE.this_motion.y, d.y);
            }
        }
    }
    // report mouse event, if keyboard is primary.
    if (is_keyboard_master() && should_report()) {
        // modify mouse report by PMW3360 motion.
        motion_to_mouse(&ETE.this_motion, &rep, is_keyboard_left(), ETE.scroll_mode);
        motion_to_mouse(&ETE.that_motion, &rep, !is_keyboard_left(), ETE.scroll_mode ^ ETE.this_have_ball);
        // store mouse report for OLED.
        ETE.last_mouse = rep;
    }
    return rep;
}

//////////////////////////////////////////////////////////////////////////////
// Split RPC

#ifdef SPLIT_KEYBOARD

static void rpc_get_info_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    ETE_info_t info = {
        .ballcnt = ETE.this_have_ball ? 1 : 0,
    };
    *(ETE_info_t *)out_data = info;
    ETE_on_adjust_layout(ETE_ADJUST_SECONDARY);
}

static void rpc_get_info_invoke(void) {
    static bool     negotiated = false;
    static uint32_t last_sync  = 0;
    static int      round      = 0;
    uint32_t        now        = timer_read32();
    if (negotiated || TIMER_DIFF_32(now, last_sync) < ETE_TX_GETINFO_INTERVAL) {
        return;
    }
    last_sync = now;
    round++;
    ETE_info_t recv = {0};
    if (!transaction_rpc_exec(ETE_GET_INFO, 0, NULL, sizeof(recv), &recv)) {
        if (round < ETE_TX_GETINFO_MAXTRY) {
            dprintf("ETE:rpc_get_info_invoke: missed #%d\n", round);
            return;
        }
    }
    negotiated          = true;
    ETE.that_enable    = true;
    ETE.that_have_ball = recv.ballcnt > 0;
    dprintf("ETE:rpc_get_info_invoke: negotiated #%d %d\n", round, ETE.that_have_ball);

    // split keyboard negotiation completed.

#    ifdef VIA_ENABLE
    // adjust VIA layout options according to current combination.
    uint8_t  layouts = (ETE.this_have_ball ? (is_keyboard_left() ? 0x02 : 0x01) : 0x00) | (ETE.that_have_ball ? (is_keyboard_left() ? 0x01 : 0x02) : 0x00);
    uint32_t curr    = via_get_layout_options();
    uint32_t next    = (curr & ~0x3) | layouts;
    if (next != curr) {
        via_set_layout_options(next);
    }
#    endif

    ETE_on_adjust_layout(ETE_ADJUST_PRIMARY);
}

static void rpc_get_motion_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    *(ETE_motion_t *)out_data = ETE.this_motion;
    // clear motion
    ETE.this_motion.x = 0;
    ETE.this_motion.y = 0;
}

static void rpc_get_motion_invoke(void) {
    static uint32_t last_sync = 0;
    uint32_t        now       = timer_read32();
    if (TIMER_DIFF_32(now, last_sync) < ETE_TX_GETMOTION_INTERVAL) {
        return;
    }
    ETE_motion_t recv = {0};
    if (transaction_rpc_exec(ETE_GET_MOTION, 0, NULL, sizeof(recv), &recv)) {
        ETE.that_motion.x = add16(ETE.that_motion.x, recv.x);
        ETE.that_motion.y = add16(ETE.that_motion.y, recv.y);
    }
    last_sync = now;
    return;
}

static void rpc_set_cpi_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    ETE_set_cpi(*(ETE_cpi_t *)in_data);
}

static void rpc_set_cpi_invoke(void) {
    if (!ETE.cpi_changed) {
        return;
    }
    ETE_cpi_t req = ETE.cpi_value;
    if (!transaction_rpc_send(ETE_SET_CPI, sizeof(req), &req)) {
        return;
    }
    ETE.cpi_changed = false;
}

#endif



//////////////////////////////////////////////////////////////////////////////
// Public API functions

bool ETE_get_scroll_mode(void) {
    return ETE.scroll_mode;
}

void ETE_set_scroll_mode(bool mode) {
    if (mode != ETE.scroll_mode) {
        ETE.scroll_mode_changed = timer_read32();
    }
    ETE.scroll_mode = mode;
}

uint8_t ETE_get_scroll_div(void) {
    return ETE.scroll_div == 0 ? ETE_SCROLL_DIV_DEFAULT : ETE.scroll_div;
}

void ETE_set_scroll_div(uint8_t div) {
    ETE.scroll_div = div > SCROLL_DIV_MAX ? SCROLL_DIV_MAX : div;
}

uint8_t ETE_get_cpi(void) {
    return ETE.cpi_value == 0 ? CPI_DEFAULT : ETE.cpi_value;
}

void ETE_set_cpi(uint8_t cpi) {
    if (cpi > CPI_MAX) {
        cpi = CPI_MAX;
    }
    ETE.cpi_value   = cpi;
    ETE.cpi_changed = true;
    if (ETE.this_have_ball) {
        pmw3360_cpi_set(cpi == 0 ? CPI_DEFAULT - 1 : cpi - 1);
        pmw3360_reg_write(pmw3360_Motion_Burst, 0);
    }
}

//////////////////////////////////////////////////////////////////////////////
// Keyboard hooks

void keyboard_post_init_kb(void) {
#ifdef SPLIT_KEYBOARD
    // register transaction handlers on secondary.
    if (!is_keyboard_master()) {
        transaction_register_rpc(ETE_GET_INFO, rpc_get_info_handler);
        transaction_register_rpc(ETE_GET_MOTION, rpc_get_motion_handler);
        transaction_register_rpc(ETE_SET_CPI, rpc_set_cpi_handler);
    }
#endif

    // read ETE configuration from EEPROM
    if (eeconfig_is_enabled()) {
        ETE_config_t c = {.raw = eeconfig_read_kb()};
        ETE_set_cpi(c.cpi);
        ETE_set_scroll_div(c.sdiv);
    }

    ETE_on_adjust_layout(ETE_ADJUST_PENDING);
    keyboard_post_init_user();
}

#if SPLIT_KEYBOARD
void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
        rpc_get_info_invoke();
        if (ETE.that_have_ball) {
            rpc_get_motion_invoke();
            rpc_set_cpi_invoke();
        }
    }
}
#endif



bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // store last keycode, row, and col for OLED
    ETE.last_kc  = keycode;
    ETE.last_pos = record->event.key;

    if (!process_record_user(keycode, record)) {
        return false;
    }

    // strip QK_MODS part.
    if (keycode >= QK_MODS && keycode <= QK_MODS_MAX) {
        keycode &= 0xff;
    }

    switch (keycode) {
#ifndef MOUSEKEY_ENABLE

// process KC_MS_BTN1~8 by myself
        // See process_action() in quantum/action.c for details.
        case KC_MS_BTN1 ... KC_MS_BTN8: {
            extern void register_mouse(uint8_t mouse_keycode, bool pressed);
            register_mouse(keycode, record->event.pressed);
            // to apply QK_MODS actions, allow to process others.
            return true;
}

#endif

        case SCRL_MO:
            ETE_set_scroll_mode(record->event.pressed);
            return false;
    }

    // process events which works on pressed only.
    if (record->event.pressed) {
        switch (keycode) {
            case REC_RST:
                ETE_set_cpi(0);
                ETE_set_scroll_div(0);
                break;
            case REC_SAVE: {
                ETE_config_t c = {
                    .cpi  = ETE.cpi_value,
                    .sdiv = ETE.scroll_div,
                };
                eeconfig_update_kb(c.raw);
            } break;

            case CPI_I100:
                add_cpi(1);
                break;
            case CPI_D100:
                add_cpi(-1);
                break;
            case CPI_I1K:
                add_cpi(10);
                break;
            case CPI_D1K:
                add_cpi(-10);
                break;

            case SCRL_TO:
                ETE_set_scroll_mode(!ETE.scroll_mode);
                break;
            case SCRL_DVI:
                add_scroll_div(1);
                break;
            case SCRL_DVD:
                add_scroll_div(-1);
                break;

            default:
                return true;
        }
        return false;
    }

    return true;
}