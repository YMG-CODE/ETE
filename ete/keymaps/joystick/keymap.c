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
      KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_LBRC,                         KC_RBRC,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_TAB,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_QUOT,                         KC_DQUO,  KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,  KC_COLN,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_DEL,  KC_PGUP,      KC_UP,    KC_RGHT,  KC_N,    KC_M,  KC_COMM,  KC_DOT,  KC_SLSH,  KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_LCTRL,KC_LALT, KC_LGUI, KC_LALT,          FN_MO13,KC_SPC,  KC_BSPC,      KC_DOWN,  KC_ENT,  FN_MO23,         KC_BSPC,  KC_DEL,  KC_RALT,  KC_AT,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
                                                            KC_PGDOWN,KC_HOME,    KC_END,   KC_LEFT 
                                                        //|--------+---------.  ,---------+--------'

  ),
    [1] = LAYOUT(
  //,--------------------------------------------------------------.                      ,--------------------------------------------------------------.
      KC_CAPS,XXXXXXX, XXXXXXX,  KC_F1,   KC_F2,   KC_F3,  KC_MS_WH_UP,                     KC_RBRC,  KC_1,    KC_2,    KC_3,  KC_HOME , KC_UP,   KC_END,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_HANJ,XXXXXXX, XXXXXXX,  KC_F4,   KC_F5,   KC_F6,  KC_MS_WH_DOWN,                   KC_DQUO,  KC_4,    KC_5,    KC_6,  KC_LEFT,  KC_DOWN, KC_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------|                      --------+--------+--------+--------+--------+--------+---------|
      KC_LSFT,XXXXXXX, XXXXXXX,  KC_F7,   KC_F8,   KC_F9,  KC_DEL,   KC_PGUP,     KC_MINS,  KC_ASTR,  KC_7,    KC_8,    KC_9,   KC_0,  KC_MS_WH_UP,KC_MS_WH_DOWN,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_LCTRL,KC_LALT, KC_LGUI, KC_LALT,          FN_MO13,KC_SPC,   KC_BSPC,     KC_SLSH,  KC_ENT,  FN_MO23,          KC_BSPC, KC_DEL,  KC_RALT, KC_AT,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
                                                           KC_PGDOWN,KC_HOME,     KC_END,   KC_PLUS 
                                                        //|--------+---------.  ,---------+--------'
  ),

    [2] = LAYOUT(
  //,--------------------------------------------------------------.                      ,--------------------------------------------------------------.
      KC_ESC,  KC_EXLM,  KC_AT,  KC_HASH, KC_DLR, KC_PERC,  KC_LBRC,                        KC_RBRC, KC_CIRC, KC_QUOT, KC_DQUO, KC_LPRN, KC_RPRN, KC_UNDS,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_TAB,  KC_AT,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_QUOT,                        KC_DQUO, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RCBR, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,   KC_PGUP,    KC_UP,    KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_LCTRL,KC_LALT, KC_LGUI, KC_LALT,          FN_MO13, KC_SPC,   KC_BSPC,    KC_DOWN,  KC_ENT,  FN_MO23,          KC_BSPC, KC_DEL,  KC_RALT, KC_AT,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
                                                            KC_PGDOWN,KC_HOME,    KC_END,   KC_LEFT 
                                                        //|--------+---------.  ,---------+--------'
  ),
   [3] = LAYOUT(
//,--------------------------------------------------------------.                      ,----------------------------------------------------------------.
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,  KC_BRIU,KC_VOLU, XXXXXXX, KC_MS_BTN1,KC_MS_UP,KC_MS_BTN2,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,  KC_BRID,KC_VOLD, XXXXXXX, KC_MS_LEFT,KC_MS_D, KC_MS_R,
  //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_MS_UP,KC_MS_BTN2,XXXXXXX,KC_MUTE, XXXXXXX, XXXXXXX, KC_MS_WH_UP,KC_MS_WH_DOWN,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          FN_MO13, XXXXXXX, XXXXXXX,     KC_MS_D,  KC_MS_R,  FN_MO23,        XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
                                                            KC_MS_WH_UP,KC_MS_WH_DOWN,KC_MS_LEFT, KC_MS_BTN1 
 )                                                       //|--------+---------.  ,---------+--------'
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



//POINTING DEVICE

// Set Parameters
uint16_t minAxisValue = 190;  // Depends on each stick
uint16_t maxAxisValue = 840;


uint8_t maxCursorSpeed = 1.5;
uint8_t maxScrollSpeed = 1;
uint8_t speedRegulator = 15;  // Lower Values Create Faster Movement

int8_t xPolarity = -1;
int8_t yPolarity = -1;
int8_t hPolarity = 1;
int8_t vPolarity = 1;

uint8_t cursorTimeout = 10;
uint8_t scrollTimeout = 100;

int16_t xOrigin, yOrigin;

uint16_t lastCursor = 0;

int16_t axisCoordinate(uint8_t pin, uint16_t origin) {
   int8_t  direction;
   int16_t distanceFromOrigin;
   int16_t range;

   int16_t position = analogReadPin(pin);

   if (origin == position) {
       return 0;
   } else if (origin > position) {
       distanceFromOrigin = origin - position;
       range              = origin - minAxisValue;
       direction          = -1;
   } else {
       distanceFromOrigin = position - origin;
       range              = maxAxisValue - origin;
       direction          = 1;
   }

   float   percent    = (float)distanceFromOrigin  / range;
   int16_t coordinate = (int16_t)(percent * 127);
   if (coordinate < 0) {
       return 0;
   } else if (coordinate > 127) {
       return 127 * direction;
   } else {
       return coordinate * direction;
   }
}

int8_t axisToMouseComponent(uint8_t pin, int16_t origin, uint8_t maxSpeed, int8_t polarity) {
   int coordinate = axisCoordinate(pin, origin);
   if (coordinate == 0) {
       return 0;
   } else {
       float percent = (float)coordinate / 127;
       return percent * maxSpeed * polarity * (abs(coordinate) / speedRegulator);
   }
}

void pointing_device_task(void) {

   
   report_mouse_t report = pointing_device_get_report();

   if(layer_state_is(L_RAISE)) {
       if (timer_elapsed(lastCursor) > scrollTimeout) {
           lastCursor = timer_read();
           report.h   = axisToMouseComponent(B5, xOrigin, maxCursorSpeed, hPolarity);
           report.v   = axisToMouseComponent(B4, yOrigin, maxCursorSpeed, vPolarity);
       }
   } else {
       if (timer_elapsed(lastCursor) > cursorTimeout) {
           lastCursor = timer_read();
           report.x   = -1*axisToMouseComponent(B5, xOrigin, maxCursorSpeed, xPolarity);
           report.y   = -1*axisToMouseComponent(B4, yOrigin, maxCursorSpeed, yPolarity);
       }
   }


 if (!readPin(D4)) {
        report.buttons |= MOUSE_BTN1;
    } else {
        report.buttons &= ~MOUSE_BTN1;
    }

   pointing_device_set_report(report);
   pointing_device_send();

}

void matrix_init_user(void) {
   xOrigin = analogReadPin(B5);
   yOrigin = analogReadPin(B4);

}