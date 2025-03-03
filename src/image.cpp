//
// Created by Joe Pettinelli on 2/17/25.
//
#include <iostream>
#include <cstring>
#include "image.h"
#include <fstream>
#include <algorithm>
#include <cassert>

using namespace std;

/**
 * The default constructor if no image data yet.
 */
Image::Image() : data(nullptr), size(0), width(0), height(0), has_header(false) {}

/**
 * The constructor used when have image size, width and height
 * but do not have the data yet.
 *
 * @param size The size of data buffer from raspicam getImageBufferSize().
 * @param width The image width.
 * @param height The image height.
 * @param encoding The image encoding.
 * @param has_header Whether the image has header.
 */
Image::Image(const size_t size, const unsigned int width, const unsigned int height,
                     const std::string& encoding, bool has_header) // NOLINT(*-pass-by-value)
    : data(nullptr), size(size), width(width), height(height), encoding(encoding), has_header(has_header) {}

/**
 * The constructor used when have actual image data.
 *
 * @param src_data The image data from raspicam grab_retrieve().
 * @param size The size of data buffer from raspicam getImageBufferSize().
 * @param width The image width.
 * @param height The image height.
 * @param encoding The image encoding.
 * @param has_header Whether the image has header.
 */
Image::Image(const unsigned char* src_data, const size_t size, const unsigned int width,
    const unsigned int height, const std::string&  encoding, bool has_header) : // NOLINT(*-pass-by-value)
    size(size), width(width), height(height), encoding(encoding), has_header(has_header) {
    data = new unsigned char[size];
    memcpy(data, src_data, size);
}

/**
 * The destructor.
 */
Image::~Image() {
    //cout << "Image memory freed." << endl << endl;
    delete[] data;
}

/**
 * Copy the constructor. Creates a new object as a copy of the
 * given object by performing a deep copy of its resources.
 *
 * @param other The object to copy from.
 */
Image::Image(const Image& other) : size(other.size), width(other.width), height(other.height),
    encoding(other.encoding), has_header(other.has_header) {
    data = new unsigned char[size];
    memcpy(data, other.data, size);
}

/**
 * Copy the assignment operator. Performs a deep copy of the
 * resources from the given object to this object.
 *
 * @param other The reference to other object to copy from.
 * @return The reference to this object after the copy.
 */
Image& Image::operator=(const Image& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        width = other.width;
        height = other.height;
        encoding = other.encoding;
        has_header = other.has_header;
        data = new unsigned char[size];
        memcpy(data, other.data, size);
    }
    return *this;
}

/**
 * Move constructor. Transfers ownership of resources from the given
 * rvalue reference to this object.
 *
 * @param other The rvalue reference whose resources will be moved.
 */
Image::Image(Image&& other) noexcept
    : data(other.data), size(other.size), width(other.width), height(other.height),
    encoding(std::move(other.encoding)), has_header(other.has_header) {
    other.data = nullptr;
    other.size = 0;
    other.width = 0;
    other.height = 0;
    other.encoding = "";
    other.has_header = false;
}

/**
 * Move assignment operator. Transfers ownership of resources
 * from the given rvalue reference to this object.
 *
 * @param other The rvalue reference whose resources to move.
 * @return The reference to this object after move.
 */
Image& Image::operator=(Image&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        width = other.width;
        height = other.height;
        encoding = std::move(other.encoding);
        has_header = other.has_header;
        other.data = nullptr;
        other.size = 0;
        other.width = 0;
        other.height = 0;
        other.encoding = "";
        other.has_header = false;
    }
    return *this;
}

/**
 * Getter function.
 *
 * @return The image data 1D.
 */
unsigned char* Image::get_data() const {
    return data;
}

/**
 * Getter function.
 *
 * @return The size of image data.
 */
size_t Image::get_size() const {
    return size;
}

/**
 * Get the image width.
 *
 * @return The image width.
 */
unsigned int Image::get_width() const {
    return width;
}

/**
 * Get the image height.
 *
 * @return The image height.
 */
unsigned int Image::get_height() const {
    return height;
}

/**
 * Get the image encoding.
 *
 * @return The image encoding.
 */
std::string Image::get_encoding() const {
    return encoding;
}

/**
 * Get whether the image has header or
 * if it has been removed.
 *
 * @return true if the image has header, else false.
 */
bool Image::get_has_header() const {
    if (encoding != "rgb") {
        assert(has_header);
    }
    return has_header;
}

/**
* Save the image to disk. User is responsible for using correct
* file extension in the file path.
*
* @param file_path The path to save the image data to.
*/
bool Image::save(const std::string& file_path) const {
    try {
        if (data == nullptr || size == 0) {
            cout << "Error: No data to save!" << endl;
            return false;
        }
        if (!check_save_extension(file_path)) {
            return false;
        }
        ofstream file (file_path, ios::binary);
        if (!file.is_open()) {
            cout << "Failed to open file for writing!" << endl;
            return false;
        }
        file.write(reinterpret_cast<char *>(data), static_cast<std::streamsize>(size));
        return true;
    } catch (const std::exception& e) {
        cout << "Caught error: " << e.what() << endl;
        return false;
    }
}

/**
* Remove the header that is 54 bytes added for images.
* Should only be called when encoding is set to rgb.
* The buffer size is calculated as width*height*3+54 by raspicam.
*/
void Image::remove_rgb_header() {
    if (encoding == "rgb") {
        if (has_header) {
            if (data != nullptr && size > 54) {
                // Remove the last 54 bytes
                auto* new_data = new unsigned char[size - 54];
                memcpy(new_data, data, size - 54);
                delete[] data;
                data = new_data;  // Point to the new buffer
                size -= 54;
                has_header = false;
                return;
            }
            cout << "Abort remove header: Data is too small or already null." << endl;
            return;
        }
        cout << "Abort remove header: Header already removed." << endl;
        return;
    }
    cout << "Abort remove header: Should only remove header for rgb encoded images." << endl;
}

/**
 * Flip a rgb encoded image horizontally. Assumes header has
 * already been removed. Do this by flipping order of each row.
 */
void Image::flip_rgb_h() const {
    if (encoding != "rgb") {
      cout << "Abort h flip: Can only flip rgb encoded images." << endl;
      return;
    }
    if (has_header) {
        cout << "Abort h flip: Should remove header first." << endl;
        return;
    }
    const size_t row_size = width * 3;  // Each row has width * 3 bytes (RGB)
    const size_t num_rows = height;
    // Iterate over each row of the image
    for (size_t row = 0; row < num_rows; ++row) {
        // Calculate the start index of the row in the 1D array
        unsigned char* row_start = data + row * row_size;
        std::reverse(row_start, row_start + row_size);
        // Swap R and B channels or the image color will be BGR
        if (row_size % 3 == 0) {
            for (size_t i = 0; i < row_size; i +=3) {
                std::swap(row_start[i], row_start[i + 2]);
            }
        }
    }
}

/**
 * Flip a rgb encoded image vertically.
 * Do this by swapping entire rows.
 */
void Image::flip_rgb_v() const {
    if (encoding != "rgb") {
        cout << "Abort v flip: Can only flip rgb encoded images." << endl;
        return;
    }
    if (has_header) {
        cout << "Abort v flip: Should remove header first." << endl;
        return;
    }
    const size_t row_size = width * 3;
    const size_t num_rows = height;
    for (size_t row = 0; row < num_rows / 2; ++row) {
        // Calculate the start index of the row in the 1D array
        unsigned char* top_row_start = data + row * row_size;
        unsigned char* bottom_row_start = data + (num_rows - row - 1) * row_size;
        // Swap rows
        for (size_t i = 0; i < row_size; ++i) {
            std::swap(top_row_start[i], bottom_row_start[i]);
        }
    }
}

/**
 * Determine whether the file path extension matches the image encoding.
 * Only check for png or jpeg because rgb encoded images can be saved
 * in many ways.
 *
 * @param file_path The file path passed by user.
 * @return Whether the file path matches the image encoding.
 */
bool Image::check_save_extension(const std::string &file_path) const {
    if (encoding == "rgb") {
        return true;
    }
    // ReSharper disable once CppTooWideScopeInitStatement
    const size_t dot_pos = file_path.rfind('.');
    if (dot_pos != std::string::npos && dot_pos < file_path.length() - 1) {
        if (file_path.substr(dot_pos + 1) == encoding) {
            return true;
        }
        cout << "Abort save: File extension does not match image encoding! Change file extension." << endl;
        return false;
    }
    cout << "Abort save: Invalid file extension!" << endl;
    return false;
}
