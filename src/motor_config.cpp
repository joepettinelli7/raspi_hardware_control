//
// Created by Joe Pettinelli on 2/17/25.
//
#include "motor_config.h"

/**
 * Documentation on pins here:
 * 1. https://www.raspberrypi.com/documentation/computers/raspberry-pi.html#gpio-pads-control
 * 2. https://pinout.xyz/pinout/wiringpi
 */
MotorConfig::MotorConfig()
    : steps_per_rev(4096),
      step_delay_ms(2),
      w_pi_pins{25, 24, 23, 22},
      step_sequence{{
          {1,0,0,1},
          {1,0,0,0},
          {1,1,0,0},
          {0,1,0,0},
          {0,1,1,0},
          {0,0,1,0},
          {0,0,1,1},
          {0,0,0,1}
      }} {
}
