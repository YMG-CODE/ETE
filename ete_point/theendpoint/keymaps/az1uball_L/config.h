// Copyright 2023 YMGWorks (@YMGWorks)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef POINTING_DEVICE_ENABLE
  #define SPLIT_POINTING_ENABLE
  #define POINTING_DEVICE_COMBINED
  
  #define PIMORONI_TRACKBALL_SCALE 6
  #define POINTING_DEVICE_TASK_THROTTLE_MS 1
  #define POINTING_DEVICE_ROTATION_180//左手スクロール・右手カーソルの場合は_RIGHTを末尾に追加
#endif