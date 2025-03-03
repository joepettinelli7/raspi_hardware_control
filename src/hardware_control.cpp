//
// Created by Joe Pettinelli on 2/18/25.
//
#include "hardware_control.h"
#include "camera_control.h"
#include "motor_control.h"

/**
 * Use nullptr until camera controller and motor controller are initialized.
 */
HardwareController::HardwareController()
    : camera_controller(nullptr), motor_controller(nullptr), initialized(false) {
}

/**
 * Destructor should clean up all hardware.
 */
HardwareController::~HardwareController() {
    cleanup_all();
}

/**
 * This should initialize camera and motor then set initialized to true.
 */
void HardwareController::initialize_all() {
    if (!initialized) {
        camera_controller = new CameraController();
        motor_controller = new MotorController();
        initialized = true;
    }
}

/**
 * Clean up camera and motor then set initialized to false.
 */
void HardwareController::cleanup_all() {
    if (initialized && camera_controller) {
        camera_controller->release_camera();
        delete camera_controller;
        camera_controller = nullptr;
    }
    if (initialized && motor_controller) {
        motor_controller->cleanup();
        delete motor_controller;
        motor_controller = nullptr;
    }
    initialized = false;
}
