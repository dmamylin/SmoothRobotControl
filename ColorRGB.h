#ifndef COLOR_RGB_H
#define COLOR_RGB_H

#include <math.h>

#include "types.h"

class ColorRGB {
private:
    u32 data;

    enum { // Numeration is from right to left [3,2,1,0]
        BLUE_BIT  = 0xFF, // 0
        GREEN_BIT = 0xFF00, // 1
        RED_BIT   = 0xFF0000, // 2
        NULL_BIT  = 0xFF000000, // 3

        BITES_IN_BIT = 8
    };

    void eraseNullBit() {
        data ^= NULL_BIT;
    }

    u8 getBit(u8 position) {
    }

public:
    inline ColorRGB(u32 color=0x0) { set(color); }
    ColorRGB(u8 red, u8 green, u8 blue) {
        set(red, green, blue);
    }
    ColorRGB(const ColorRGB& color) {
        this->data = color.data;
    }

    inline ColorRGB& operator=(const ColorRGB& color) {
        this->data = color.data;
        return *this;
    }

    inline u32 getAsNumber() const { return data; }
    inline u8 getRed() const { 

    inline void set(u32 color) { data = color; eraseNullBit(); }
    inline void set(u8 red, u8 green, u8 blue) {

    }

    inline friend bool operator==(const ColorRGB& lhs, const ColorRGB& rhs) {
        return lhs.data == rhs.data;
    }
    inline friend bool operator!=(const ColorRGB& lhs, const ColorRGB& rhs) {
        return lhs.data != rhs.data;
    }
};

#endif