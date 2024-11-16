/*
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
#include "config_common.h"

#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_COMBINED
  
#define ANALOG_JOYSTICK_X_AXIS_PIN B4
#define ANALOG_JOYSTICK_Y_AXIS_PIN B5
#define ANALOG_JOYSTICK_AXIS_MIN 200
#define ANALOG_JOYSTICK_AXIS_MAX 800
#define ANALOG_JOYSTICK_SPEED_REGULATOR 30
#define ANALOG_JOYSTICK_READ_INTERVAL 10
#define ANALOG_JOYSTICK_SPEED_MAX 2