//
// Created by Joe Pettinelli on 2/17/25.
//
#include <iostream>
#include "raspicam/raspicam_still.h"
#include "camera_control.h"
#include "image.h"

using namespace std;

/**
 * Initialize the camera configuration once at beginning
 * of the program and open the camera.
 */
CameraController::CameraController() {
    camera.setWidth(config.image_width);
    camera.setHeight(config.image_height);
    camera.setSharpness(config.sharpness);
    camera.setContrast(config.contrast);
    camera.setBrightness(config.brightness);
    camera.setSaturation(config.saturation);
    camera.setISO(config.iso);
    camera.setEncoding(raspicam::RASPICAM_ENCODING_PNG);
    camera.setExposure(raspicam::RASPICAM_EXPOSURE_AUTO);
    cout << "Initialize camera success." << endl;
}

/**
 * Open the camera. Should not be called until user sets
 * desired image width, height, and encoding.
 */
void CameraController::open_camera() {
    if (camera.open()) {
        cout << "Camera open success." << endl;
    } else {
        cout << "Camera open failed." << endl;
    }
}

/**
 * Capture data for image using raspberry pi camera.
 *
 * @return The 1D bytes representing the image + the header + padding which
 *          changes depending on the encoding being used. png is RGBA
 *          and jpeg is RGB.
 */
Image CameraController::capture_image() {
    cout << "Take single image." << endl;
    // size is Header + Image Data + Padding
    const unsigned int size = camera.getImageBufferSize();
    const auto data = new unsigned char[size];
    camera.grab_retrieve(data, size);
    Image image(data, size, config.image_width, config.image_height, config.encoding, true);
    delete[] data;
    return image;
}

/**
 * After done using the camera, release it.
 */
void CameraController::release_camera() {
    camera.release();
    cout << "Cleanup camera success." << endl;
}

/**
 * Set the image width.
 *
 * @param new_width The new image width. Should be multiple of 320.
 */
void CameraController::set_image_width(const unsigned int new_width) {
    config.image_width = new_width;
    camera.setWidth(new_width);
}

/**
 * Set the image height.
 *
 * @param new_height The new image height. Should be multiple of 240.
 */
void CameraController::set_image_height(const unsigned int new_height) {
    config.image_height = new_height;
    camera.setHeight(new_height);
}

/**
 * Set the image encoding.
 *
 * @param new_encoding The new image encoding. Only allow png, jpeg, or rgb.
 */
void CameraController::set_image_encoding(const std::string& new_encoding) {
    if (new_encoding == "png") {
        camera.setEncoding(raspicam::RASPICAM_ENCODING_PNG);
    } else if (new_encoding == "jpeg") {
        camera.setEncoding(raspicam::RASPICAM_ENCODING_JPEG);
    } else if (new_encoding == "rgb") {
        camera.setEncoding(raspicam::RASPICAM_ENCODING_RGB);
    } else {
        throw std::invalid_argument("Use png, jpeg, or rgb instead.");
    }
    config.encoding = new_encoding;
}

/**
 * Get the current image width.
 *
 * @return The image width.
 */
unsigned int CameraController::get_image_width() const {
    return config.image_width;
}

/**
 * Get the current image height.
 *
 * @return The image height.
 */
unsigned int CameraController::get_image_height() const {
    return config.image_height;
}

/**
 * Get the current image encoding.
 *
 * @return The image encoding. Should only be png, jpeg, or rgb.
 */
std::string CameraController::get_image_encoding() const {
    return config.encoding;
}
