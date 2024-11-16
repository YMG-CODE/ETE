/*
Copyright 2021 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)
Copyright 2023 kushima8
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

#pragma once

#include "quantum.h"
#include "lib/reex/reex.h"

extern void (*pointing_device_set_button)(uint8_t btn);
extern void (*pointing_device_clear_button)(uint8_t btn);

// clang-format off

#define LAYOUT( \
         L00, L01, L02, L03, L04, L05, L06, L35,       R31, R00, R01, R02, R03, R04, R05, R06, \
         L10, L11, L12, L13, L14, L15, L16, L27,       R21, R10, R11, R12, R13, R14, R15, R16, \
         L20, L21, L22, L23, L24, L25, L26, L40,       R40, R22, R23, R24, R25, R26, R27, R28, \
         L30, L31, L32, L33,      L34, L36, L41,       R41, R30, R32,      R33, R34, R35, R36, \
         RE1A,RE1B,                                                                  RE2A,RE2B \
   ) \
  { \
    { L00,   L01,   L02,   L03,   L04,   L05,  L06,   L35 }, \
    { L10,   L11,   L12,   L13,   L14,   L15,  L16,   L27 }, \
    { L20,   L21,   L22,   L23,   L24,   L25,  L26,   L40 }, \
    { L30,   L31,   L32,   L33,   KC_NO, L34,  L36,   L41 }, \
    { RE1A, RE1B, KC_NO, KC_NO,  KC_NO, KC_NO,KC_NO, KC_NO }, \
    { R06,   R05,   R04,   R03,   R02,   R01,  R00,   R31 }, \
    { R16,   R15,   R14,   R13,   R12,   R11,  R10,   R21 }, \
    { R28,   R27,   R26,   R25,   R24,   R23,  R22,   R40 }, \
    { R36,   R35,   R34,   R33,   KC_NO, R32,  R30,   R41 }, \
    { RE2A, RE2B,  KC_NO, KC_NO,  KC_NO, KC_NO,KC_NO, KC_NO } \
  }

