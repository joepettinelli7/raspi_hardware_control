//
// Created by Joe Pettinelli on 2/18/25.
//
#ifndef HARDWARE_CONTROL_H
#define HARDWARE_CONTROL_H

#include "camera_control.h"
#include "motor_control.h"

class HardwareController {

public:
    HardwareController();
    ~HardwareController();
    void initialize_all();
    void cleanup_all();
    CameraController* camera_controller;
    MotorController* motor_controller;

private:
    bool initialized;
};

#endif //HARDWARE_CONTROL_H
