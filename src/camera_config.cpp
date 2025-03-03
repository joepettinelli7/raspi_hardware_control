//
// Created by Joe Pettinelli on 2/17/25.
//
#include "camera_config.h"

/**
 * Github: https://github.com/cedricve/raspicam/blob/master/src/raspicam_still.cpp
 */
CameraConfig::CameraConfig()
    : sharpness(0), // -100 - 100
      contrast(0), // -100 - 100
      brightness(50),  // 0 - 100
      saturation(0), // -100 - 100
      iso(700), // 100 - 800
      image_width(320), // Should be multiple of 320
      image_height(240),  // make multiple of 240
      encoding("png")
{
}
