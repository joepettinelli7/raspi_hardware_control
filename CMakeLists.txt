cmake_minimum_required(VERSION 3.10)
project(raspi_hardware_control)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake" "/usr/local" ${CMAKE_PREFIX_PATH})
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
set(CMAKE_BUILD_TYPE Release)

# Include directories
include_directories(include)

# Find required packages
find_package(raspicam REQUIRED)
find_library(WIRINGPI_LIB wiringPi)
find_package(pybind11 REQUIRED)
find_package(Python 3 REQUIRED)

if (NOT raspicam_FOUND)
    message(FATAL_ERROR "raspicam not found!")
endif()
if (NOT WIRINGPI_LIB)
    message(FATAL_ERROR "wiringPi not found!")
endif()
if (NOT pybind11_FOUND)
    message(FATAL_ERROR "pybind11 not found!")
endif()
if (NOT Python_FOUND)
    message(FATAL_ERROR "Python not found!")
endif()

# Create executable for standalone c++
add_executable(cpp_raspi_hw_ctrl
        src/main.cpp
        src/hardware_control.cpp
        src/camera_control.cpp
        src/camera_config.cpp
        src/motor_control.cpp
        src/motor_config.cpp
        src/image.cpp
)

# Create python module for python bindings
pybind11_add_module(py_raspi_hw_ctrl
        py_src/py_hardware_control.cpp
        src/hardware_control.cpp
        src/motor_control.cpp
        src/motor_config.cpp
        src/camera_control.cpp
        src/camera_config.cpp
        src/image.cpp
)

# Do not need pybind for c++
target_link_libraries(cpp_raspi_hw_ctrl
        PUBLIC
        ${raspicam_LIBS}
        ${WIRINGPI_LIB}
)

# Need pybind for c++
target_link_libraries(py_raspi_hw_ctrl
        PUBLIC
        ${raspicam_LIBS}
        ${WIRINGPI_LIB}
        pybind11::module
)

# Install the C++ executable
install(TARGETS cpp_raspi_hw_ctrl
    DESTINATION bin
)

# Install the Python module
install(TARGETS py_raspi_hw_ctrl
    DESTINATION lib/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/dist-packages
)
