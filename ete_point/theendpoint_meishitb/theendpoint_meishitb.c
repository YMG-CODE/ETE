/*
Copyright 2022 aki27
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
#include <math.h>
#include "theendpoint_meishitb.h"
#include "wait.h"
#include "debug.h"
#include <stdio.h>
#include "transactions.h"
#include "pointing_device.h"
extern const pointing_device_driver_t pointing_device_driver;


// Invert vertical scroll direction
#ifndef ETE_SCROLL_INV_DEFAULT
#    define ETE_SCROLL_INV_DEFAULT 1
#endif

#ifndef ETE_CPI_OPTIONS
#    define ETE_CPI_OPTIONS { 250, 500, 750, 1000, 1250 }
#    ifndef ETE_CPI_DEFAULT
#       define ETE_CPI_DEFAULT 1
#    endif
#endif
#ifndef ETE_CPI_DEFAULT
#    define ETE_CPI_DEFAULT 1
#endif

#ifndef ETE_SCROLL_DIVIDERS
#    define ETE_SCROLL_DIVIDERS { 1, 2, 3, 4, 5, 6 }
#    ifndef ETE_SCROLL_DIV_DEFAULT
#       define ETE_SCROLL_DIV_DEFAULT 4
#    endif
#endif
#ifndef ETE_SCROLL_DIV_DEFAULT
#    define ETE_SCROLL_DIV_DEFAULT 4
#endif


#ifndef ETE_ROTATION_ANGLE
#    define ETE_ROTATION_ANGLE { -60, -45, -30, -15, 0, 15, 30, 45, 60 }
#    ifndef ETE_ROTATION_DEFAULT
#       define ETE_ROTATION_DEFAULT 1
#    endif
#endif
#ifndef ETE_ROTATION_DEFAULT
#    define ETE_ROTATION_DEFAULT 1
#endif


ETE_config_t ETE_config;
uint16_t cpi_array[] = ETE_CPI_OPTIONS;
uint16_t scrl_div_array[] = ETE_SCROLL_DIVIDERS;
uint16_t angle_array[] = ETE_ROTATION_ANGLE;
#define CPI_OPTION_SIZE (sizeof(cpi_array) / sizeof(uint16_t))
#define SCRL_DIV_SIZE (sizeof(scrl_div_array) / sizeof(uint16_t))
#define ANGLE_SIZE (sizeof(angle_array) / sizeof(uint16_t))


// Trackball State
bool     BurstState        = false;  // init burst state for Trackball module
uint16_t MotionStart       = 0;      // Timer for accel, 0 is resting state

// Scroll Accumulation
static int16_t h_acm       = 0;
static int16_t v_acm       = 0;


void pointing_device_init_kb(void) {
    // set the CPI.
    pointing_device_set_cpi(cpi_array[ETE_config.cpi_idx]);
}


report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {

    double rad = angle_array[ETE_config.rotation_angle] * (M_PI / 180) * -1;
    int8_t x_rev =  + mouse_report.x * cos(rad) - mouse_report.y * sin(rad);
    int8_t y_rev =  + mouse_report.x * sin(rad) + mouse_report.y * cos(rad);

    if (ETE_get_scroll_mode()) {
        // rock scroll direction
        if (abs(x_rev) > abs(y_rev)) {
            y_rev = 0;
        } else {
            x_rev = 0;
        }

        // accumulate scroll
        h_acm += x_rev * ETE_config.scrl_inv;
        v_acm += y_rev * ETE_config.scrl_inv * -1;

        int8_t h_rev = h_acm >> scrl_div_array[ETE_config.scrl_div];
        int8_t v_rev = v_acm >> scrl_div_array[ETE_config.scrl_div];

        // clear accumulated scroll on assignment

        if (h_rev != 0) {
            if (mouse_report.h + h_rev > 127) {
                h_rev = 127 - mouse_report.h;
            } else if (mouse_report.h + h_rev < -127) {
                h_rev = -127 - mouse_report.h;
            }
            mouse_report.h += h_rev;
            h_acm -= h_rev << scrl_div_array[ETE_config.scrl_div];
        }
        if (v_rev != 0) {
            if (mouse_report.v + v_rev > 127) {
                v_rev = 127 - mouse_report.v;
            } else if (mouse_report.v + v_rev < -127) {
                v_rev = -127 - mouse_report.v;
            }
            mouse_report.v += v_rev;
            v_acm -= v_rev << scrl_div_array[ETE_config.scrl_div];
        }

        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        mouse_report.x = x_rev;
        mouse_report.y = y_rev;
    }

    return pointing_device_task_user(mouse_report);
}



bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    // xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    
    if (!process_record_user(keycode, record)) return false;

    switch (keycode) {
#ifndef MOUSEKEY_ENABLE
        // process KC_MS_BTN1~8 by myself
        // See process_action() in quantum/action.c for details.
        case KC_MS_BTN1 ... KC_MS_BTN8: {
            extern void register_button(bool, enum mouse_buttons);
            register_button(record->event.pressed, MOUSE_BTN_MASK(keycode - KC_MS_BTN1));
            return false;
        }
#endif

    }

    if (keycode == CPI_SW && record->event.pressed) {
        ETE_config.cpi_idx = (ETE_config.cpi_idx + 1) % CPI_OPTION_SIZE;
        eeconfig_update_kb(ETE_config.raw);
        pointing_device_set_cpi(cpi_array[ETE_config.cpi_idx]);
    }

    if (keycode == SCRL_SW && record->event.pressed) {
        ETE_config.scrl_div = (ETE_config.scrl_div + 1) % SCRL_DIV_SIZE;
        eeconfig_update_kb(ETE_config.raw);
    }
    
    if (keycode == ROT_R15 && record->event.pressed) {
        ETE_config.rotation_angle = (ETE_config.rotation_angle + 1) % ANGLE_SIZE;
        eeconfig_update_kb(ETE_config.raw);
    }

    if (keycode == ROT_L15 && record->event.pressed) {
        ETE_config.rotation_angle = (ANGLE_SIZE + ETE_config.rotation_angle - 1) % ANGLE_SIZE;
        eeconfig_update_kb(ETE_config.raw);
    }

    if (keycode == SCRL_IN && record->event.pressed) {
        ETE_config.scrl_inv = - ETE_config.scrl_inv;
        eeconfig_update_kb(ETE_config.raw);
    }

    if (keycode == SCRL_TO && record->event.pressed) {
        { ETE_config.scrl_mode ^= 1; }
    }

    if (keycode == SCRL_MO) {
        { ETE_config.scrl_mode ^= 1; }
    }

    return true;
}


void eeconfig_init_kb(void) {
    ETE_config.cpi_idx = ETE_CPI_DEFAULT;
    ETE_config.scrl_div = ETE_SCROLL_DIV_DEFAULT;
    ETE_config.rotation_angle = ETE_ROTATION_DEFAULT;
    ETE_config.scrl_inv = ETE_SCROLL_INV_DEFAULT;
    ETE_config.scrl_mode = false;
    eeconfig_update_kb(ETE_config.raw);
    eeconfig_init_user();
}


void matrix_init_kb(void) {
    // is safe to just read CPI setting since matrix init
    // comes before pointing device init.
    ETE_config.raw = eeconfig_read_kb();
    //if (ETE_config.cpi_idx > CPI_OPTION_SIZE) // || ETE_config.scrl_div > SCRL_DIV_SIZE || ETE_config.rotation_angle > ANGLE_SIZE)
    //{
        //eeconfig_init_kb();
    //}
    eeconfig_init_kb();
    matrix_init_user();
}


bool ETE_get_scroll_mode(void) {
    return ETE_config.scrl_mode;
}

void ETE_set_scroll_mode(bool mode) {
    ETE_config.scrl_mode = mode;
}