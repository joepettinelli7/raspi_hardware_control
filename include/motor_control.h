//
// Created by Joe Pettinelli on 2/17/25.
//
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "motor_config.h"

class MotorController {

public:
    MotorController();
    void set_to_output_mode() const;
    void cleanup() const;
    void rotate(unsigned int degrees, int direction) const;
    void set_pins(unsigned int pin1, unsigned int pin2, unsigned int pin3, unsigned int pin4);

private:
    MotorConfig config;
    void clockwise_step(unsigned int semi_step) const;
    void counter_clockwise_step(unsigned int semi_step) const;
};

#endif //MOTOR_CONTROL_H
