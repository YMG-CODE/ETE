 /* Copyright 2022 YMGWORKS
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "analog.h"
#include "pointing_device.h"


// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
   //,--------------------------------------------------------------.                      ,--------------------------------------------------------------.
      KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_LBRC,KC_SPC,         KC_ENT,  KC_RBRC,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_QUOT,KC_PGDOWN,     KC_UP, KC_DQUO,  KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,  KC_COLN,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTRL,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_PGUP,KC_END,        KC_LEFT, KC_RGHT,  KC_N,    KC_M,  KC_COMM,  KC_DOT,  KC_SLSH, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_TAB,KC_LALT, KC_LGUI, KC_PSCR,              KC_SPC,KC_ENT,  KC_HOME,      KC_END,  KC_DOWN, KC_SPC ,          KC_BSPC,  KC_DEL,  KC_RALT,  KC_AT,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_DEL, KC_BSPC,KC_UP,KC_DOWN ,                                                                                       KC_LEFT,KC_RGHT,KC_UP,KC_DOWN  
 ),
    [1] = LAYOUT(
  //,--------------------------------------------------------------.                      ,--------------------------------------------------------------.
      KC_CAPS,KC_HANJ, XXXXXXX,  KC_F1,   KC_F2,   KC_F3,  KC_MS_WH_UP, KC_PGDOWN,   KC_END,  KC_RBRC,  KC_1,    KC_2,    KC_3,  KC_HOME , KC_UP,   KC_END,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,XXXXXXX, XXXXXXX,  KC_F4,   KC_F5,   KC_F6,  KC_MS_WH_DOWN,KC_HOME,    KC_PLUS,  KC_DQUO,  KC_4,    KC_5,    KC_6,  KC_LEFT,  KC_DOWN, KC_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------|                      --------+--------+--------+--------+--------+--------+---------|
      KC_LCTRL,XXXXXXX, XXXXXXX,  KC_F7,   KC_F8,   KC_F9,  KC_DEL,   KC_PGUP,     KC_MINS,  KC_ASTR,  KC_7,    KC_8,    KC_9,   KC_0,  KC_MS_WH_UP,KC_MS_WH_DOWN,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_TAB,KC_LALT, KC_LGUI, KC_PSCR,          KC_SPC,KC_SPC,   KC_BSPC,     KC_SLSH,  KC_ENT,  KC_SPC,          KC_BSPC, KC_DEL,  KC_RALT, KC_AT,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_DEL,KC_BSPC,KC_UP,KC_DOWN ,                                                                                        KC_UP,KC_DOWN ,KC_UP,KC_DOWN 
  //|--------+--------+--------+--------+--------+--------+--------+---------.  ,---------+-------+--------+--------+--------+--------+--------+---------'
  ),

    [2] = LAYOUT(
  //,--------------------------------------------------------------.                      ,--------------------------------------------------------------.
      KC_ESC,  KC_EXLM,  KC_AT,  KC_HASH, KC_DLR, KC_PERC,  KC_LBRC,KC_PGDOWN,    KC_END,  KC_RBRC, KC_CIRC, KC_QUOT, KC_DQUO, KC_LPRN, KC_RPRN, KC_UNDS,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,  KC_AT,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_QUOT, KC_HOME,    KC_PLUS, KC_DQUO, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RCBR, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,   KC_PGUP,    KC_UP,    KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_TAB,KC_LALT, KC_LGUI, KC_PSCR,          KC_SPC, KC_SPC,   KC_BSPC,      KC_DOWN,  KC_ENT,  KC_SPC,                KC_BSPC, KC_DEL,  KC_RALT, KC_AT,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_LEFT,KC_RGHT,KC_UP,KC_DOWN ,                                                                                     KC_UP,KC_DOWN ,KC_DEL, KC_BSPC  
  //|--------+--------+--------+--------+--------+--------+--------+---------.  ,---------+-------+--------+--------+--------+--------+--------+---------'
  ),
   [3] = LAYOUT(
//,--------------------------------------------------------------.                      ,----------------------------------------------------------------.
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX,KC_MS_WH_UP,   KC_MS_LEFT, XXXXXXX,  KC_BRIU,KC_VOLU, XXXXXXX, KC_MS_BTN1,KC_MS_UP,KC_MS_BTN2,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX,KC_MS_WH_DOWN, KC_MS_BTN1, XXXXXXX,  KC_BRID,KC_VOLD, XXXXXXX, KC_MS_LEFT,KC_MS_D, KC_MS_R,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_MS_UP,KC_MS_BTN2,XXXXXXX,KC_MUTE, XXXXXXX, XXXXXXX, KC_MS_WH_UP,KC_MS_WH_DOWN,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_SPC, XXXXXXX, XXXXXXX,     KC_MS_D,  KC_MS_R, KC_SPC,            XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_WH_L, KC_WH_R, KC_UP,KC_DOWN ,                                                                                   KC_UP,KC_DOWN ,KC_LEFT,KC_RGHT
//|--------+--------+--------+--------+--------+--------+-------+---------.   ,---------+--------+--------+--------+--------+--------+--------+---------'
)
};

#define L_BASE 0
#define L_LOWER 1
#define L_RAISE 2
#define L_ADJUST 3

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}

#ifdef ENCODER_ENABLE
const uint8_t rt_matrix[][4][2] = {
    {{4,0},{4,1}},
    {{4,2},{4,3}},
    {{9,0},{9,1}},
    {{9,2},{9,3}},


};

bool encoder_update_user(uint8_t index, bool clockwise) {
    keypos_t key;

    int      cw = 0;
    if (clockwise) cw = 1;
    key.row          = rt_matrix[index][cw][0];
    key.col          = rt_matrix[index][cw][1];

    action_exec((keyevent_t){.key = key, .pressed = true, .time = (timer_read() | 1)});
    action_exec((keyevent_t){.key = key, .pressed = false, .time = (timer_read() | 1)});

    return false;
}
#endif


