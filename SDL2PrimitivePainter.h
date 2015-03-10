#ifndef SDL2_PRIMITIVE_PAINTER
#define SDL2_PRIMITIVE_PAINTER

#include "utilities.h"

#include <SDL2\SDL.h>
#include <math.h>

class SDL2PrimitivePainter {
public:
    point2i fromScreenCoords(const point2i& pointOnScreen, const point2i& newCenter) {
        int newX = pointOnScreen.x - newCenter.x;
        int newY = newCenter.y - pointOnScreen.y;

        return point2i(newX, newY);
    }

    point2i toScreenCoords(const point2i& oldPoint, const point2i& oldCenter) {
        int newX = oldPoint.x + oldCenter.x;
        int newY = oldCenter.y - oldPoint.y;

        return point2i(newX, newY);
    }

    inline bool onSurface(SDL_Surface* s, s32 x, s32 y) {
        return x >= 0 && y >= 0 && x < s->w && y < s->h;
    }

    inline void setPixel(SDL_Surface* s, s32 x, s32 y, const ColorRGB& color) {
        if (onSurface(s, x, y)) {
            ((u32*)s->pixels)[y * s->w + x] = color.getAsNumber();
        }        
    }

    inline void setPixel(SDL_Surface* s, const point2i& point, const ColorRGB& color) {
        setPixel(s, point.x, point.y, color);
    }

    inline void setPixelUnsafe(SDL_Surface* s, s32 x, s32 y, const ColorRGB& color) {
        ((u32*)s->pixels)[y * s->w + x] = color.getAsNumber();
    }

    void drawLine(SDL_Surface* s, s32 x1, s32 y1, s32 x2, s32 y2, const ColorRGB& color) {
        s32 start, end, i;
        f64 k, b;
        s32 dx = x1 - x2;
        s32 dy = y1 - y2;

        if (abs(dx) >= abs(dy)) {
            start = min(x1, x2);
            end = max(x1, x2);

            start = min(max(start, 0), s->w);
            end = max(min(s->h, end), 0);

            k = ((f64)(y1 - y2)) / dx;
            b = ((f64)(x1 * y2 - x2 * y1)) / dx;

            for (i = start; i <= end; i++) {
                s32 y = (s32)(k * i + b);

                setPixel(s, i, y, color);
            }
        }
        else {
            start = min(y1, y2);
            end = max(y1, y2);

            start = min(max(start, 0), s->h);
            end = max(min(s->w, end), 0);

            k = ((f64)(dx)) / dy;
            b = -((f64)(x1 * y2 - x2 * y1)) / dy;

            for (i = start; i <= end; i++) {
                s32 x = (s32)(k*i + b);

                setPixel(s, x, i, color);
            }
        }
    }

    inline void drawLine(SDL_Surface* s, const point2i& p1, const point2i& p2, const ColorRGB& color) {
        drawLine(s, p1.x, p1.y, p2.x, p2.y, color);
    }

};

#endif