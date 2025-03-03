//
// Created by Joe Pettinelli on 2/17/25.
//
#ifndef CAMERA_CONTROL_H
#define CAMERA_CONTROL_H

#include "raspicam/raspicam_still.h"
#include "camera_config.h"
#include "image.h"

class CameraController {

public:
    CameraController();
    void open_camera();
    Image capture_image();
    void release_camera();
    void set_image_width(unsigned int new_width);
    void set_image_height(unsigned int new_height);
    void set_image_encoding(const std::string& new_encoding);
    [[nodiscard]] unsigned int get_image_width() const;
    [[nodiscard]] unsigned int get_image_height() const;
    [[nodiscard]] std::string get_image_encoding() const;

private:
    CameraConfig config;
    raspicam::RaspiCam_Still camera;
};

#endif //CAMERA_CONTROL_H
