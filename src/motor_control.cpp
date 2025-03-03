//
// Created by Joe Pettinelli on 2/17/25.
//
#include <iostream>
#include <chrono>
#include <thread>
#include <wiringPi.h>
#include "motor_control.h"

using namespace std;

/**
 * Initialize the motor once at beginning of program.
 * Make sure setup is successful and then set pins to output mode.
 */
MotorController::MotorController() {
    if (wiringPiSetup() == -1) {
        cerr << "Initialize motor failed." << endl;
    } else {
        cout << "Initialize motor success." << endl << endl;
    }
}

/**
 * Set the pins to output mode to send signal.
 */
void MotorController::set_to_output_mode() const {
    for (const unsigned int w_pi_pin : config.w_pi_pins) {
        pinMode(w_pi_pin, OUTPUT);
    }
}

/**
 * Set the current pins to input mode when done using them.
 */
void MotorController::cleanup() const {
    for (const unsigned int w_pi_pin : config.w_pi_pins) {
        pinMode(w_pi_pin, INPUT);
    }
    cout << "Cleanup motor success." << endl;
}

/**
 * Rotate the motor in either direction for certain number
 * of degrees.
 *
 * @param degrees Degrees to rotate the motor.
 * @param direction The direction to rotate the motor.
 */
void MotorController::rotate(const unsigned int degrees, const int direction) const {
    const unsigned int num_steps = (config.steps_per_rev * degrees) / 360;
    int semi_step_counter = 0;
    for (int step = 0; step < num_steps; step++) {
        if (direction == 1) {
            clockwise_step(semi_step_counter);
        } else {
            counter_clockwise_step(semi_step_counter);
        }
        semi_step_counter = (semi_step_counter + 1) % 8;
        this_thread::sleep_for(chrono::milliseconds(config.step_delay_ms));
    }
}

/**
 * Set the pins being used on raspberry pi. Does not clean up
 * the previous pins being used. Should call cleanup() before setting
 * new pins. Also, after this function is called, set_to_output_mode()
 * should be called.
 *
 * @param pin1 The first pin.
 * @param pin2 The second pin.
 * @param pin3 The third pin.
 * @param pin4 The fourth pin.
 */
void MotorController::set_pins(const unsigned int pin1, const unsigned int pin2, const unsigned int pin3,
    const unsigned int pin4) {
    config.w_pi_pins[0] = pin1;
    config.w_pi_pins[1] = pin2;
    config.w_pi_pins[2] = pin3;
    config.w_pi_pins[3] = pin4;
}

/**
 * Make a single clockwise step.
 *
 * @param semi_step The semi-step ranging from 1-8.
 */
void MotorController::clockwise_step(const unsigned int semi_step) const {
    digitalWrite(config.w_pi_pins[0], config.step_sequence[semi_step][0]);
    digitalWrite(config.w_pi_pins[1], config.step_sequence[semi_step][1]);
    digitalWrite(config.w_pi_pins[2], config.step_sequence[semi_step][2]);
    digitalWrite(config.w_pi_pins[3], config.step_sequence[semi_step][3]);
}

/**
 * Make a single counter-clockwise step.
 *
 * @param semi_step The semi-step ranging from 1-8.
 */
void MotorController::counter_clockwise_step(const unsigned int semi_step) const {
    digitalWrite(config.w_pi_pins[0], config.step_sequence[semi_step][3]);
    digitalWrite(config.w_pi_pins[1], config.step_sequence[semi_step][2]);
    digitalWrite(config.w_pi_pins[2], config.step_sequence[semi_step][1]);
    digitalWrite(config.w_pi_pins[3], config.step_sequence[semi_step][0]);
}
