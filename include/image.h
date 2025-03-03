//
// Created by Joe Pettinelli on 2/17/25.
//
#ifndef IMAGE_DATA_H
#define IMAGE_DATA_H

#include <iostream>
#include <cstddef>

class Image {

public:
    Image();
    explicit Image(size_t size, unsigned int width, unsigned int height, const std::string &encoding, bool has_header);
    Image(const unsigned char* src_data, size_t size, unsigned int width, unsigned int height,
          const std::string &encoding, bool has_header);
    ~Image();
    Image(const Image& other);
    Image& operator=(const Image& other);
    Image(Image&& other) noexcept;
    Image& operator=(Image&& other) noexcept;
    [[nodiscard]] unsigned char* get_data() const;
    [[nodiscard]] size_t get_size() const;
    [[nodiscard]] unsigned int get_width() const;
    [[nodiscard]] unsigned int get_height() const;
    [[nodiscard]] std::string get_encoding() const;
    [[nodiscard]] bool get_has_header() const;
    [[nodiscard]] bool save(const std::string& file_path) const;
    void remove_rgb_header();
    void flip_rgb_h() const;
    void flip_rgb_v() const;

private:
    unsigned char* data;
    size_t size;
    unsigned int width;
    unsigned int height;
    std::string encoding;
    [[nodiscard]] bool check_save_extension(const std::string& file_path) const;
    bool has_header;
};

#endif //IMAGE_DATA_H
