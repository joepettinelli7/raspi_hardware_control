# raspi_hardware_control

## What does this project do?
This project develops a way to control a camera and/or stepper motor that is attached to a Raspberry Pi. It can be integrated into a C++ project or a Python project using the Python bindings made with pybind11 (https://github.com/pybind/pybind11). It has the ability to:
1. Take PNG, JPEG, or RGB-encoded images and store them in a custom Image class in which the raw image data is unsigned char* type.
2. Save the images to disk.
3. With Python bindings, convert PNG or JPEG-encoded images to PIL Image objects, or convert RGB-encoded images to NumPy ndarray objects.
4. Rotate a stepper motor in either direction for a user-specified number of degrees.

## Hardware used:
1. Raspberry Pi 4 Model B (4GB) with Raspberry Pi OS (legacy, 32-bit) Debian Bullseye (https://www.raspberrypi.com/products/raspberry-pi-4-model-b/).
     - This project will not work on newer OS or 64-bit OS because it depends on the MMAL (Multimedia Abstraction Layer) API.
3. Raspberry Pi Camera Modue V2 (https://www.raspberrypi.com/products/camera-module-v2/).
4. ULN2003 28BYJ-48 4-Phase Stepper Motor with 5V Drive Board (https://www.amazon.com/HiLetgo-ULN2003-28BYJ-48-Stepper-4-phase/dp/B00LPK0E5A).
5. Tenergy NiMH 6V 2000 mAh battery pack (Optional).

## How can users get started with the project?
1. Enable legacy camera
     - sudo raspi-config
     - Interface Options
     - Legacy Camera
     - Would you like to enable legacy camera support? Yes
2. Install cmake (https://cmake.org/download/).
     - sudo apt-get install cmake
3. Install raspicam (https://github.com/cedricve/raspicam)
     - git clone https://github.com/cedricve/raspicam.git
     - Fix issue with raspicam_still.h (https://github.com/cedricve/raspicam/issues/31)
     - cd raspicam
     - mkdir build
     - cd build
     - cmake ..
     - make
     - sudo make install
     - sudo ldconfig
3. Install wiringpi (https://github.com/WiringPi/WiringPi/tree/master)
     - git clone https://github.com/WiringPi/WiringPi.git
     - cd WiringPi
     - ./build debian
     - mv debian-template/wiringpi_3.14_armhf.deb .
     - sudo apt install ./wiringpi_3.14_armhf.deb
5. Install pybind 11 (https://github.com/pybind/pybind11)
     - git clone https://github.com/pybind/pybind11.git
     - cd pybind11
     - mkdir build
     - cd build
     - cmake ..
     - make
     - sudo make install
6. Install this project
     - git clone https://github.com/joepettinelli7/raspi_hardware_control.git
     - cd raspi_hardware_control
     - mkdir build
     - cd build
     - cmake ..
     - make
     - sudo make install
     - cpp_raspi_hw_ctrl (This will run the C++ main.cpp file)

For example python usage see py_raspi_hw_ctrl_test.py.
