#include "..\ColorRGB.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    ColorRGB color1(500,0,0);

    printf("0x%08x; Red: %u, Green: %u, Blue: %u\n", color1.getAsNumber(),
        color1.getRed(), color1.getGreen(), color1.getBlue());
    printf("%d\n", sizeof(ColorRGB));

    system("pause");

    return 0;
}