#ifndef COLOR_RGB_H
#define COLOR_RGB_H

#include "types.h"

class ColorRGB {
private:
    u32 data;

    enum : u32 { // Numeration is from right to left [3,2,1,0]
        BLUE_BYTE  = 0x000000FF, // 0
        GREEN_BYTE = 0x0000FF00, // 1
        RED_BYTE   = 0x00FF0000, // 2
        NULL_BYTE  = 0xFF000000, // 3

        BITS_IN_BYTE = 8,

        BLUE_POSITION  = 0,
        GREEN_POSITION = 1,
        RED_POSITION   = 2,
        NULL_POSITION  = 3
    };

    inline void eraseByte(u32 byte) { data &= ~byte; }

    u8 getByte(u8 position) const { return u8(data >> position * BITS_IN_BYTE); }

public:
    inline ColorRGB(u32 color=0x0)             { set(color); }
    inline ColorRGB(u8 red, u8 green, u8 blue) { set(red, green, blue); }
    inline ColorRGB(const ColorRGB& color)     { set(color.data); }

    inline ColorRGB& operator=(const ColorRGB& color) { set(color.data); return *this; }
    inline ColorRGB& operator=(const u32 color)       { set(color); return *this; }
    inline ColorRGB& operator=(const s32 color)       { set((u32)color); return *this; }

    inline u32 getAsNumber() const { return data; }
    inline u8 getRed() const       { return getByte(RED_POSITION); }
    inline u8 getGreen() const     { return getByte(GREEN_POSITION); }
    inline u8 getBlue() const      { return getByte(BLUE_POSITION); }

    inline const ColorRGB& setRed(u8 red) {
        u32 redData = u32(red) << RED_POSITION * BITS_IN_BYTE;
        eraseByte(RED_BYTE);
        data ^= redData;
        return *this;
    }
    inline const ColorRGB& setGreen(u8 green) {
        u32 greenData = u32(green) << GREEN_POSITION * BITS_IN_BYTE;
        eraseByte(GREEN_BYTE);
        data ^= greenData;
        return *this;
    }
    inline const ColorRGB& setBlue(u8 blue) {
        u32 blueData = u32(blue) << BLUE_POSITION * BITS_IN_BYTE;
        eraseByte(BLUE_BYTE);
        data ^= blueData;
        return *this;
    }
    inline const ColorRGB& set(u32 color) { 
        data = color;
        eraseByte(NULL_BYTE);
        return *this;
    }
    inline const ColorRGB& set(u8 red, u8 green, u8 blue) {
        setRed(red);
        setGreen(green);
        setBlue(blue);
        eraseByte(NULL_BYTE);
        return *this;
    }

    inline friend bool operator==(const ColorRGB& lhs, const ColorRGB& rhs) {
        return lhs.data == rhs.data;
    }
    inline friend bool operator!=(const ColorRGB& lhs, const ColorRGB& rhs) {
        return lhs.data != rhs.data;
    }
};

#endif