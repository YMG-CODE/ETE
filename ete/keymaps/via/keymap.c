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
      KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_LBRC,                         KC_RBRC,  KC_Y,    KC_U,    KC_I,    KC_O,  KC_P,    KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_TAB,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_DQUO,                         KC_DQUO,  KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_DEL,  KC_PGUP,    KC_UP,    KC_RGHT,   KC_N,    KC_M,  KC_COMM,  KC_DOT,  KC_SLSH, KC_UNDS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_LCTRL,KC_LALT, KC_LGUI, KC_LGUI,          FN_MO13, KC_SPC, KC_BSPC,      KC_DOWN,  KC_ENT,   FN_MO23,         KC_BSPC,  KC_DEL, KC_RALT,KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
                                                            KC_PGDOWN, KC_HOME,     KC_END,   KC_LEFT 
                                                        //|--------+---------.  ,---------+--------'

  ),
    [1] = LAYOUT(
  //,--------------------------------------------------------------.                      ,--------------------------------------------------------------.
      KC_CAPS,   KC_Q,    KC_W,    KC_F1,   KC_F2,  KC_F3,  KC_MS_WH_UP,                     KC_RBRC,  KC_1,    KC_2,    KC_3,    KC_O,    KC_P,   KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_HANJ,   KC_A,    KC_S,    KC_F4,   KC_F5,  KC_F6,  KC_MS_WH_DOWN,                   KC_QUOT,  KC_4,    KC_5,    KC_6,    KC_L,   KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|                      --------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,  KC_Z,    KC_X,    KC_F7,   KC_F8,  KC_F9,  KC_MS_BTN1,KC_MS_UP,     KC_UP,   KC_RGHT,  KC_7,    KC_8,    KC_9,    KC_0,  KC_SLSH, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_LCTRL,KC_LALT, KC_LGUI, KC_LALT,         FN_MO13, KC_MS_LEFT, KC_MS_D,    KC_DOWN,  KC_ENT,  FN_MO23,         KC_BSPC,  KC_DEL,  KC_RALT, KC_GRV,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
                                                           KC_MS_BTN2, KC_MS_R,  KC_END,  KC_LEFT 
                                                        //|--------+---------.  ,---------+--------'
  ),

    [2] = LAYOUT(
  //,--------------------------------------------------------------.                      ,--------------------------------------------------------------.
      KC_ESC,   KC_Q,    KC_W,   KC_1,    KC_2,    KC_3,  KC_LBRC,                         KC_RBRC,  KC_1,    KC_2,    KC_3,    KC_O,    KC_P,   KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_TAB,   KC_A,    KC_S,   KC_4,    KC_5,    KC_6,  KC_QUOT,                         KC_QUOT,  KC_4,    KC_5,    KC_6,    KC_L,   KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,  KC_Z,    KC_X,   KC_7,    KC_8,    KC_9,    KC_DEL, KC_MS_UP,       KC_UP,   KC_RGHT,  KC_7,    KC_8,    KC_9,    KC_0,   KC_SLSH, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_LCTRL,KC_LALT, KC_LGUI, KC_LALT,          FN_MO13, KC_SPC, KC_BSPC,     KC_DOWN,  KC_ENT,  FN_MO23,         KC_BSPC,  KC_DEL,  KC_RALT, KC_GRV,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
                                                            KC_MS_R, KC_HOME,     KC_END,  KC_LEFT 
                                                        //|--------+---------.  ,---------+--------'
  ),
   [3] = LAYOUT(
//,--------------------------------------------------------------.                      ,----------------------------------------------------------------.
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, KC_MS_WH_UP,                    XXXXXXX,  KC_BRIU,KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, KC_MS_WH_DOWN,                  XXXXXXX,  KC_BRID,KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_L,  KC_MS_UP,    KC_UP,   KC_RGHT,  XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          FN_MO13, KC_MS_BTN1,KC_MS_D,    KC_DOWN,  KC_ENT,  FN_MO23,          XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
                                                            KC_MS_R, KC_MS_BTN2,   KC_END,  KC_LEFT 
 )                                                       //|--------+---------.  ,---------+--------'
};

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

