#ifndef IMAGE_H
#define IMAGE_H

#include <cassert>
#include <string>
#include <vector>

#include <iostream>
#include "vecmath.h"

// Simple image class
class Image
{
  public:
    // Instantiate an image of given width and height
    // All pixels are set to black (0, 0, 0) by default.
    Image(int w, int h)
    {
        _width = w;
        _height = h;
        _data.resize(_width * _height);
    }

    // Return width of image
    int getWidth() const {
        return _width;
    }

    // Return height of image
    int getHeight() const {
        return _height;
    }

    // Set pixel to given RGB
    void setPixel(int x, int y, const Vector3f &color) {
        assert(x >= 0 && x < _width);
        assert(y >= 0 && y < _height);
        _data[y * _width + x] = color;
    }

    // Return pixel at given x, y coordinates
    const Vector3f & getPixel(int x, int y) const {
        assert(x >= 0 && x < _width);
        assert(y >= 0 && y < _height);
        return _data[y * _width + x];
    }

    // Initialize all pixels in image to given RGB color.
    void setAllPixels(const Vector3f &color) {
        for (int i = 0; i < _width * _height; ++i) {
            _data[i] = color;
        }
    }

    char * getPixels(){
        char * pixels = new char[_width * _height * 3];
        for(int y = 0; y < _height; y++) {
            for(int x = 0; x < _width; x++) {
                for(int c = 0; c < 3; c++) {
                    pixels[3 * (_width * y + x) + c] = getPixel(x,y)[c] * 255;
                }
            }
        }
        return pixels;

    }

    // Reads PNG image and return new image instance.
    static Image * loadPNG(const std::string &filename);

    // Save contents of image to given file name in PNG file format.
    void savePNG(const std::string &filename) const;

    // Return an absolute difference betweenthe given images
    static Image * compare(Image *img1, Image *img2);


  private:
    std::vector<Vector3f> _data;
    int _width;
    int _height;
};

#endif // IMAGE_H
