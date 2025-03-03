//
// Created by Joe Pettinelli on 2/17/25.
//
#ifndef CAMERA_CONFIG_H
#define CAMERA_CONFIG_H
#include <string>

struct CameraConfig {
    CameraConfig();
    int sharpness;
    int contrast;
    unsigned int brightness;
    int saturation;
    int iso;
    unsigned int image_width;
    unsigned int image_height;
    std::string encoding;
};

#endif //CAMERA_CONFIG_H
