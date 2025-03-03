//
// Created by Joe Pettinelli on 2/17/25.
//
#ifndef MOTOR_CONFIG_H
#define MOTOR_CONFIG_H

#include <array>

struct MotorConfig {
    MotorConfig();
    unsigned int steps_per_rev;
    unsigned int step_delay_ms;
    std::array<unsigned int, 4> w_pi_pins;
    std::array<std::array<unsigned int, 4>, 8> step_sequence;
};

#endif //MOTOR_CONFIG_H
