//
// Created by Joe Pettinelli on 2/17/25.
//
#include <iostream>
#include "hardware_control.h"
#include "image.h"

using namespace std;

/**
 * This function will test that the hardware can be controlled
 * successfully. It will take an image, save the image, and move
 * the motor both ways. Then it will release the camera and
 * set the GPIO pins to input.
 */
int main() {
    cout << "Initializing hardware..." << endl;
    HardwareController hardware_controller;
    hardware_controller.initialize_all();
    // Change image config and take image.
    hardware_controller.camera_controller->set_image_width(640);
    hardware_controller.camera_controller->set_image_height(480);
    hardware_controller.camera_controller->set_image_encoding("png");
    hardware_controller.camera_controller->open_camera();
    const Image img = hardware_controller.camera_controller->capture_image();
    const std::string file_path = "./test_image.png";
    const bool img_saved = img.save(file_path);
    cout << "Image was saved successfully? " << img_saved << endl;
    // Change pins and test motor.
    cout << "Moving motor..." << endl;
    hardware_controller.motor_controller->set_pins(25, 24, 23, 22);
    hardware_controller.motor_controller->set_to_output_mode();
    hardware_controller.motor_controller->rotate(90, 1);
    hardware_controller.motor_controller->rotate(90, -1);
    cout << endl << "Cleaning up hardware..." << endl;
    hardware_controller.cleanup_all();
    return 0;
}
