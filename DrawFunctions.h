#ifndef DRAW_FUNCTIONS_H
#define DRAW_FUNCTIONS_H

void drawEndPoint(SDL_Surface* display) {
    SDL_Rect dstRect;
    point2i posOnScreen = g_Painter.toScreenCoords(g_endPoint, USER_COORD_CENTER);

    dstRect.x = posOnScreen.x - END_POINT_W / 2;
    dstRect.y = posOnScreen.y - END_POINT_H / 2;
    dstRect.w = END_POINT_W;
    dstRect.h = END_POINT_H;

    SDL_FillRect(display, &dstRect, END_POINT_COLOR);
}

void drawEndDir(SDL_Surface* display) {
    point2i start = g_Painter.toScreenCoords(g_endPoint, USER_COORD_CENTER);
    point2i end = g_Painter.toScreenCoords(point2i(vec2(g_endPoint.x, g_endPoint.y) + END_VEC_LEN * g_endDir), USER_COORD_CENTER);

    g_Painter.drawLine(display, start.x, start.y, end.x, end.y, END_POINT_COLOR);
}

void drawRobot(SDL_Surface* display) {
    SDL_Rect dstRect;
    point2i posOnScreen = g_Painter.toScreenCoords(point2i(g_rPos), USER_COORD_CENTER);
    point2i dirOnScreen = g_Painter.toScreenCoords(point2i(ROBOT_DIR_LEN * g_rDir + g_rPos), USER_COORD_CENTER);

    dstRect.x = posOnScreen.x - ROBOT_W / 2;
    dstRect.y = posOnScreen.y - ROBOT_H / 2;
    dstRect.w = ROBOT_W;
    dstRect.h = ROBOT_H;

    SDL_FillRect(display, &dstRect, ROBOT_COLOR);
    g_Painter.drawLine(display, posOnScreen, dirOnScreen, ROBOT_COLOR);
}

void drawPath(SDL_Surface* display) {
    for (std::list<point2i>::iterator it = g_path.begin(); it != g_path.end(); it++) {
        g_Painter.setPixel(display, it->x, it->y, 0xFF0000);
    }
}

void drawPolygonalChain(SDL_Surface* display) {
    auto itPrev = g_path.begin();
    auto itCurr = g_path.begin();
    if (!g_path.empty()) {
        itCurr++;
    }

    for (; itCurr != g_path.end(); itCurr++, itPrev++) {
        g_Painter.drawLine(display, *itPrev, *itCurr, ColorRGB(255, 0, 0));
    }
}

#endif