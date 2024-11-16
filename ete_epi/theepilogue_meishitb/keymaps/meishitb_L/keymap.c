// Copyright 2023 YMGWorks (@YMGWorks)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include <stdio.h>


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
   //,---------------------------------------------------------------------.     ,-----------------------------------------------------------------------.
      KC_ESC,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_MUTE, KC_SPC,       KC_ENT,  KC_TAB,  KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,     KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
      KC_LSFT, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_HOME, KC_PGDN,      KC_UP,   KC_END,  KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,  KC_COLN,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
      KC_LCTL, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,    KC_PGUP, KC_END,       KC_LEFT, KC_RGHT, KC_N,    KC_M,   KC_COMM,  KC_DOT, KC_SLSH,  KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
      KC_TAB,  KC_LALT, KC_LGUI, KC_PSCR,         MO(1),   KC_ENT,  KC_HOME,      KC_END,  KC_DOWN, MO(2) ,          KC_BSPC,  KC_DEL, KC_RALT,  KC_AT,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
      KC_PGUP,KC_PGDN,                                                                                                                  KC_LEFT, KC_RIGHT
  ),
    [1] = LAYOUT(
  //,----------------------------------------------------------------------.     ,-----------------------------------------------------------------------.
      KC_CAPS,KC_CAPS, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,  KC_1,   KC_2,   KC_3,    KC_HOME , KC_UP,    KC_END,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
      KC_TRNS,XXXXXXX, XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,  KC_4,   KC_5,   KC_6,    KC_LEFT,  KC_DOWN,  KC_RGHT,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
      KC_TRNS,XXXXXXX, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,  KC_7,   KC_8,   KC_9,    KC_0,  KC_MS_WH_UP,KC_MS_WH_DOWN,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
      KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,  MO(3),          KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
     KC_TRNS, KC_TRNS,                                                                                                                    KC_BSPC, KC_DEL 
  //|--------+--------+--------+--------+--------+--------+--------+---------.  ,--------+-------+--------+--------+--------+---------+--------+---------'
  ),

    [2] = LAYOUT(
  //,------------------------------------------------------------------------.    ,----------------------------------------------------------------------.
     KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_CIRC, KC_QUOT, KC_DQUO, KC_LPRN, KC_RPRN, KC_UNDS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+-------+--------+--------+--------+---------|
     KC_LSFT,  KC_AT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, XXXXXXX,XXXXXXX, XXXXXXX, KC_LBRC, KC_RCBR, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+-------+--------+--------+--------+---------|
     KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, XXXXXXX,XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+-------+--------+--------+--------+---------|
     KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS,          MO(3),   KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+-------+--------+--------+--------+---------|
     KC_MS_WH_LEFT,KC_MS_WH_RIGHT,                                                                                                     KC_TRNS, KC_TRNS  
  //|--------+--------+--------+--------+--------+--------+--------+---------.  ,---------+-------+--------+-------+--------+--------+--------+---------'
  ),
   [3] = LAYOUT(
//,-------------------------------------------------------------------------.    ,-----------------------------------------------------------------------.
     RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_TRNS, KC_VOLU, KC_BRIU, KC_MS_BTN1,KC_MS_UP,KC_MS_BTN2,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
     RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, KC_MS_BTN2, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_MS_BTN2, KC_VOLD,KC_BRID, KC_MS_LEFT,KC_MS_D, KC_MS_R,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
     ROT_L15, ROT_R15, SCRL_IN, SCRL_MO, XXXXXXX,KC_MS_BTN2, KC_MS_BTN1,XXXXXXX, XXXXXXX,KC_MS_BTN1,KC_MS_BTN2,KC_MUTE, XXXXXXX, XXXXXXX,KC_MS_WH_UP,KC_MS_WH_DOWN,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
     CPI_SW, SCRL_SW, SCRL_TO, XXXXXXX,          KC_TRNS, XXXXXXX, KC_MS_BTN1,   KC_MS_BTN1, XXXXXXX, KC_TRNS,          XXXXXXX, XXXXXXX, XXXXXXX ,XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------+---------|  |--------+--------+--------+--------+--------+--------+--------+---------|
     XXXXXXX, XXXXXXX,                                                                                                                 XXXXXXX ,XXXXXXX
  //|--------+--------+--------+--------+--------+--------+-------+----------.   ,-------+--------+--------+--------+--------+--------+--------+---------'
 )
};
// clang-format on

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case 3:
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            break;
        default:
            set_auto_mouse_enable(true);
            break;
    }
    return state;
}
#endif

bool encoder_update_user(uint8_t index, bool clockwise) {
    keypos_t key;
    if(index == 0){
     if(clockwise){
         key.row = 4;
         key.col = 0;
       } else {
         key.row = 4;
         key.col = 1;
       }
      
       uint8_t layer = layer_switch_get_layer(key);
       uint8_t keycode = keymap_key_to_keycode(layer,key);
       tap_code16(keycode);
    
    }else if(index == 1){
      if(clockwise){
         key.row = 9;
         key.col = 0;
       } else {
         key.row = 9;
         key.col = 1;
       }
      
       uint8_t layer = layer_switch_get_layer(key);
       uint8_t keycode = keymap_key_to_keycode(layer,key);
       tap_code16(keycode);
}
return false; 
}