/*
Copyright 2023 YMGWORKS

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

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "analog.h"
#include "pointing_device.h"
//#include "drivers/sensors/analog_joystick.h"
#include "gpio.h"
#include "wait.h"
#include "timer.h"
#include "iqs5xx.h"

#define FN  MO(1)
#define BALL  MO(2)

enum custom_keycodes {
    KC_MY_BTN1 = 0x8000,
    KC_MY_BTN2,
    KC_MY_BTN3,
    KC_MY_BTN4,
    KC_MY_BTN5,
    KC_MY_SCR,
    KC_TC_INC,
    KC_TC_DEC,
    KC_SD_V,
    KC_SD_H,
};

typedef union {
  uint32_t raw;
  struct {
    bool     tap : 1;
  };
} user_config_t;
user_config_t user_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
   //,---------------------------------------------------------------------.     ,-----------------------------------------------------------------------.
      KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_MUTE,KC_SPC,       KC_ENT,  KC_TAB,  KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+---------+--------|
      KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_HOME,KC_PGDOWN,    KC_UP,  KC_END,  KC_H,     KC_J,    KC_K,    KC_L,   KC_SCLN, KC_COLN,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+---------+--------|
      KC_LCTRL,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_PGUP,KC_END,       KC_LEFT,  KC_RGHT,  KC_N,    KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
      KC_TAB,    KC_LALT, KC_LGUI, KC_PSCR,         MO(1),KC_ENT,  KC_HOME,      KC_END,  KC_DOWN, MO(2) ,          KC_BSPC, KC_DEL, KC_RALT, KC_AT,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_VOLU, KC_VOLD,                                                                                                                  KC_UP,  KC_DOWN  
 ),
    [1] = LAYOUT(
  //,----------------------------------------------------------------------.     ,-----------------------------------------------------------------------.
      KC_CAPS,KC_HANJ, XXXXXXX,  KC_F1,   KC_F2,   KC_F3,  KC_TRNS, KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_1,   KC_2,   KC_3,    KC_HOME , KC_UP,    KC_END,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+---------+--------|
      KC_TRNS,XXXXXXX, XXXXXXX,  KC_F4,   KC_F5,   KC_F6,  KC_TRNS, KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_4,   KC_5,   KC_6,    KC_LEFT,  KC_DOWN,  KC_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+---------+--------|
      KC_TRNS,XXXXXXX, XXXXXXX,  KC_F7,   KC_F8,   KC_F9,  KC_TRNS, KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_7,   KC_8,   KC_9,    KC_0,  KC_MS_WH_UP,KC_MS_WH_DOWN,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,  KC_TRNS, MO(3),          KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_TRNS,KC_TRNS,                                                                                                                    KC_BSPC, KC_DEL 
  //|--------+--------+--------+--------+--------+--------+--------+---------.  ,---------+-------+--------+--------+--------+--------+--------+---------'
  ),

    [2] = LAYOUT(
  //,------------------------------------------------------------------------.    ,----------------------------------------------------------------------.
      KC_ESC,  KC_EXLM,  KC_AT,  KC_HASH, KC_DLR, KC_PERC,  KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS, KC_CIRC, KC_QUOT, KC_DQUO, KC_LPRN, KC_RPRN, KC_UNDS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
      KC_LSFT,  KC_AT,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RCBR, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
      KC_LCTRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_TAB,KC_TRNS,KC_TRNS, KC_TRNS,             MO(3),    KC_TRNS, KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      KC_MS_WH_UP,KC_MS_WH_DOWN,                                                                                                        KC_TRNS, KC_TRNS  
  //|--------+--------+--------+--------+--------+--------+--------+---------.  ,---------+-------+--------+--------+--------+--------+--------+---------'
  ),
   [3] = LAYOUT(
//,-------------------------------------------------------------------------.    ,-----------------------------------------------------------------------.
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,     XXXXXXX,  XXXXXXX, KC_BRIU,KC_VOLU, XXXXXXX, KC_MS_BTN1,KC_MS_UP,KC_MS_BTN2,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,     XXXXXXX,  XXXXXXX, KC_BRID,KC_VOLD, XXXXXXX, KC_MS_LEFT,KC_MS_D, KC_MS_R,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,KC_MUTE, XXXXXXX, XXXXXXX,KC_MS_WH_UP,KC_MS_WH_DOWN,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_TRNS, XXXXXXX, XXXXXXX,     XXXXXXX,  XXXXXXX, KC_TRNS,            XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |---------+--------+--------+--------+--------+--------+--------+--------|
     XXXXXXX, XXXXXXX,                                                                                                                    XXXXXXX,XXXXXXX
  //|--------+--------+--------+--------+--------+--------+-------+----------.   ,---------+--------+--------+--------+--------+--------+--------+--------'
)
};


//POINTING DEVICE マスターをカーソル移動、サブをスクロール
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    right_report.h = right_report.x;
    right_report.v = right_report.y;
    right_report.x = 0;
    right_report.y = 0;
    return pointing_device_combine_reports(left_report, right_report);
 }





keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 4, .col = 2},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 4, .col = 3},
    .pressed = false
}; 

void matrix_scan_user(void) {
    if (IS_PRESSED(encoder1_ccw)) {
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }

    if (IS_PRESSED(encoder1_cw)) {
        encoder1_cw.pressed = false;
        encoder1_cw.time = (timer_read() | 1);
        action_exec(encoder1_cw);
    }
}

bool is_hold = false;

void encoder_layer_up(void) { 
  if (get_highest_layer(layer_state|default_layer_state) == 3 ) {
    layer_clear();
  } else {
    layer_move(get_highest_layer(layer_state)+1); 
  }
} 

void encoder_layer_down(void) { 
    if (get_highest_layer(layer_state|default_layer_state) == 0 ) {
      layer_move(3);
    } else {
      layer_move(get_highest_layer(layer_state)-1); 
    }
}  

void encoder_ccw(void) {
  encoder1_ccw.pressed = true;
  encoder1_ccw.time = (timer_read() | 1);
  is_hold ? encoder_layer_down() : action_exec(encoder1_ccw);
}

void encoder_cw(void) {
  encoder1_cw.pressed = true;
  encoder1_cw.time = (timer_read() | 1);
  is_hold ? encoder_layer_up() : action_exec(encoder1_cw);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { clockwise ? encoder_cw() : encoder_ccw(); }
    return true;
}




void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
  tap_mode = user_config.tap;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t pressed_time = 0;
  switch (keycode) {  
      case KC_BTN1 ... KC_BTN5:
        if (record->event.pressed) {
          pointing_device_set_button(1 << (keycode - KC_BTN1));
        } else {
          pointing_device_clear_button(1 << (keycode - KC_BTN1));
        }
      return false;
      break;
    case KC_F24:
      if (record->event.pressed) {    
        pressed_time = record->event.time;
        if(!is_hold){
            encoder_layer_up();
        }
        is_hold = false;
      } else {
          if((record->event.time - pressed_time) > TAPPING_TERM) {
            is_hold = true;
          }
      }
      return false;
    case KC_F23:
      if (record->event.pressed) {    
        user_config.tap = !user_config.tap;  
        eeconfig_update_user(user_config.raw); 
        tap_mode = user_config.tap;
      } 
      return false;  
    default:
      return true;
  }
};


