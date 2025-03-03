//
// Created by Joe Pettinelli on 2/18/25.
//
#include <pybind11/pybind11.h>
#include "image.h"
#include "camera_control.h"
#include "motor_control.h"
#include "hardware_control.h"
#include <vector>

namespace py = pybind11;

PYBIND11_MODULE(py_raspi_hw_ctrl, m) {

    py::class_<Image>(m, "Image")
        .def(py::init<>(), "Constructor 1")
        .def(py::init<size_t, unsigned int, unsigned int, std::string, bool>(), "Constructor 2")
        .def(py::init<const unsigned char*, size_t, int, int, std::string, bool>(), "Constructor 3")
        .def("get_data", [](const Image& self) {
            void* ptr = self.get_data();
            ssize_t item_size = 1;
            auto format = "B";
            std::vector shape = {self.get_size()};
            std::vector strides = {1};
            bool readonly = false;
            return py::memoryview::from_buffer(ptr, item_size, format, shape, strides, readonly);
        })
        .def("get_size", &Image::get_size)
        .def("get_width", &Image::get_width)
        .def("get_height", &Image::get_height)
        .def("get_encoding", &Image::get_encoding)
        .def("save", &Image::save)
        .def("remove_rgb_header", &Image::remove_rgb_header)
        .def("flip_rgb_h", &Image::flip_rgb_h)
        .def("flip_rgb_v", &Image::flip_rgb_v);

    py::class_<CameraController>(m, "CameraController")
        .def(py::init<>())
        .def("open_camera", &CameraController::open_camera)
        .def("capture_image", &CameraController::capture_image)
        .def("release_camera", &CameraController::release_camera)
        .def("set_image_width", &CameraController::set_image_width)
        .def("set_image_height", &CameraController::set_image_height)
        .def("set_image_encoding", &CameraController::set_image_encoding)
        .def("get_image_width", &CameraController::get_image_width)
        .def("get_image_height", &CameraController::get_image_height)
        .def("get_image_encoding", &CameraController::get_image_encoding);

    py::class_<MotorController>(m, "MotorController")
        .def(py::init<>())
        .def("set_to_output_mode", &MotorController::set_to_output_mode)
        .def("cleanup", &MotorController::cleanup)
        .def("rotate", &MotorController::rotate)
        .def("set_pins", &MotorController::set_pins);

    py::class_<HardwareController>(m, "HardwareController")
        .def(py::init<>())
        .def("initialize_all", &HardwareController::initialize_all)
        .def("cleanup_all", &HardwareController::cleanup_all)
        .def_readwrite("camera_controller", &HardwareController::camera_controller)
        .def_readwrite("motor_controller", &HardwareController::motor_controller);
}
