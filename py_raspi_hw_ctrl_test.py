from py_raspi_hw_ctrl import HardwareController
from PIL import Image
import io
import numpy as np


if __name__ == "__main__":
    hw = HardwareController()
    hw.initialize_all()
    cc = hw.camera_controller
    cc.set_image_width(320)
    cc.set_image_height(240)

    # This
    cc.set_image_encoding("png")
    cc.open_camera()
    img = cc.capture_image()
    img.save("./test_img.png")
    pil_img = Image.open(io.BytesIO(img.get_data()))

    # Or use this instead
    # cc.set_image_encoding("rgb")
    # cc.open_camera()
    # img = cc.capture_image()
    # img.remove_rgb_header()
    # img.flip_rgb_v()
    # arr = np.frombuffer(img.get_data(), dtype=np.uint8)
    # arr = arr.reshape((img.get_height(), img.get_width(), 3))

    # For motor control
    mc = hw.motor_controller
    mc.set_pins(25, 24, 23, 22)
    mc.set_to_output_mode()
    mc.rotate(90, 1)
    mc.rotate(90, -1)

    hw.cleanup_all()
