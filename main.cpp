#ifdef _WIN32
    #include <SDL2/SDL.h>
#elif __linux__
    #include <SDL2/SDL.h>
#endif

#include <stdio.h>
#include <list>
  
#include "utilities.h"
#include "algorithm.h"

#define CAPTION    "Smooth path"
#define WIDTH      1024
#define HEIGHT     768
#define FILL_COLOR 0x0

#ifdef _WIN32
	#undef main
	#define _CRT_SECURE_NO_WARNINGS
	#pragma comment(lib, "SDL2.lib")
#endif

//Пользовательские координаты: центр - в центре экрана, ось X - вправо, ось Y - вверх
//Координаты окна (родные для SDL): центра - в левом верхнем углу, ось X - вправо, ось Y - вниз

//Константы:
    //Направления и координаты:
        const point2i USER_COORD_CENTER = point2i(WIDTH / 2, HEIGHT / 2); //Центр пользовательской СК, выраженный в координатах окна
        const vec2 DEFAULT_END_DIR = vec2(0.0, 1.0); //Результирующее направление по умолчанию
        const vec2 DEFAULT_END_POINT = vec2(0.0, 0.0);
        const double STOP_WHEN = 0.01; //Условие остановки
        const double EPSILON = 4.0; //Точность достижения цели
    //Для отрисовки:
        const double END_VEC_LEN = 20.0; //Длина вектора результирующего направления (в пикселях)
        const double ROBOT_DIR_LEN = 30.0; //Длина вектора направления робота (в пикселях)
        const int END_POINT_W = 8; //Ширина конечной точки (в пикселях)
        const int END_POINT_H = 8; //Высота конечной точки (в пикселях)
        const int ROBOT_H = 8; //Длина робота (в пикселях)
        const int ROBOT_W = 8; //Ширина робота (в пикселях)
        const u32 END_POINT_COLOR = 0x00FF00;
        const u32 ROBOT_COLOR = 0xFF0000;

//runtime global variables
point2i g_endPoint; //Координата конечной точки (в пользовательской СК, в пикселях)
vec2 g_endDir; //Конечное направление. Должен быть единичной длины (в пользовательской СК)
vec2 g_rPos(0.0, 0.0); //Положение робота (в пользовательской СК, в пикселях)
vec2 g_rDir(0.0, 1.0); //Единичный вектор направления робота (в пользовательской СК)
bool g_onTarget;
std::list<point2i> path; //Хранит точки пути для отрисовки
std::list<point2vec2> targets; //Список целей

void init() {
    g_endPoint = DEFAULT_END_POINT;
    g_endDir = DEFAULT_END_DIR;
    g_onTarget = false;

    targets.push_back(point2<vec2>(vec2(-100.0, -100.0), vec2(0.0, -1.0)));
    targets.push_back(point2<vec2>(vec2(100.0, -100.0), vec2(0.0, 1.0)));
	targets.push_back(point2<vec2>(vec2(100.0, 100.0), vec2(-1.0, 0.0)));
	targets.push_back(point2<vec2>(vec2(-100.0, 100.0), vec2(0.0, -1.0)));
	targets.push_back(point2<vec2>(vec2(-100.0, -100.0), vec2(1.0, 0.0)));
}

void drawEndPoint(SDL_Surface* display) {
    SDL_Rect dstRect;
    point2i posOnScreen = toScreenCoords(g_endPoint, USER_COORD_CENTER);

    dstRect.x = posOnScreen.x - END_POINT_W / 2;
    dstRect.y = posOnScreen.y - END_POINT_H / 2;
    dstRect.w = END_POINT_W;
    dstRect.h = END_POINT_H;

    SDL_FillRect(display, &dstRect, END_POINT_COLOR);
}

void drawEndDir(SDL_Surface* display) {
    point2i start = toScreenCoords(g_endPoint, USER_COORD_CENTER);
    point2i end = toScreenCoords(point2i(vec2(g_endPoint.x, g_endPoint.y) + END_VEC_LEN * g_endDir), USER_COORD_CENTER);

    drawLine(display, start.x, start.y, end.x, end.y, END_POINT_COLOR);
}

void drawRobot(SDL_Surface* display) {
    SDL_Rect dstRect;
    point2i posOnScreen = toScreenCoords(point2i(g_rPos), USER_COORD_CENTER);
    point2i dirOnScreen = toScreenCoords(point2i(ROBOT_DIR_LEN * g_rDir + g_rPos), USER_COORD_CENTER);

    dstRect.x = posOnScreen.x - ROBOT_W / 2;
    dstRect.y = posOnScreen.y - ROBOT_H / 2;
    dstRect.w = ROBOT_W;
    dstRect.h = ROBOT_H;

    SDL_FillRect(display, &dstRect, ROBOT_COLOR);
    drawLine(display, posOnScreen, dirOnScreen, ROBOT_COLOR);
}

void drawPath(SDL_Surface* display) {
    for (std::list<point2i>::iterator it = path.begin(); it != path.end(); it++) {
        setPixel(display, it->x, it->y, 0xFF0000);
    }
}

int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* ren = NULL;
    SDL_Surface* display = NULL;
    bool run = true;
    bool endPointExists = true;
    bool mousePressed = false;

    SDL_Init(SDL_INIT_VIDEO);
    init();

    window = SDL_CreateWindow(CAPTION, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    display = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);

    while (run) {
        SDL_Event ev;
        SDL_Texture* tex;

        //Обработка событий
        SDL_PollEvent(&ev);
        if (ev.type == SDL_QUIT || 
           (ev.type ==SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)) {
            run = false;
        } else if (ev.type == SDL_MOUSEBUTTONDOWN && !mousePressed) {
            mousePressed = true;
            if (endPointExists) {
                g_endPoint = fromScreenCoords(point2i(ev.button.x, ev.button.y), USER_COORD_CENTER);
                endPointExists = false;
            } else {
                int mouseX, mouseY, dx, dy;
                point2i inUserCoords;

                SDL_GetMouseState(&mouseX, &mouseY);
                inUserCoords = fromScreenCoords(point2i(mouseX, mouseY), USER_COORD_CENTER);

                dx = inUserCoords.x - g_endPoint.x;
                dy = inUserCoords.y - g_endPoint.y;
                if ( dx == 0 && dy == 0 ) {
                    g_endDir = DEFAULT_END_DIR;
                } else {
                    g_endDir = vec2(dx, dy);
                    g_endDir.Normalize();
                }
                endPointExists = true;
                path.clear();

				g_onTarget = false;
            }
        } else if (ev.type == SDL_MOUSEBUTTONUP) {
            mousePressed = false;
        } else if (ev.type == SDL_KEYDOWN) {
            if (ev.key.keysym.sym == SDLK_SPACE) {
                vec2 endVec = vec2((double)g_endPoint.x, (double)g_endPoint.y);
                if ((endVec - g_rPos).Length() <= EPSILON) {
					g_onTarget = targets.empty() ? true : false;

                    if (!g_onTarget) {
						g_endPoint = point2i(targets.front().x);
						g_endDir = targets.front().y;
						targets.pop_front();
					}
                    endVec = vec2((double)g_endPoint.x, (double)g_endPoint.y);					
                }

				if (!g_onTarget) {
					vec2 vel = step(g_rPos, endVec, g_rDir, g_endDir); //X - угловая скорость, Y - линейная
					path.push_back(toScreenCoords(point2i((int)g_rPos.x, (int)g_rPos.y), USER_COORD_CENTER));

					double sinw = sin(vel.x);
					double cosw = cos(vel.x);
					vec2 temp = g_rDir;

					g_rDir.x = temp.x * cosw - temp.y * sinw;
					g_rDir.y = temp.x * sinw + temp.y * cosw;
					g_rDir.Normalize();

					g_rPos += vel.y * g_rDir;								
				}

				/*#ifdef __linux__
					system("clear");
				#elif _WIN32
					system("cls");
				#endif
				printf("Distance to: %lf; on target: %d\n", (endVec - g_rPos).Length(), g_onTarget ? 1 : 0);*/
            }
        }

        if ( !endPointExists ) {
            int mouseX, mouseY, dx, dy;
            point2i inUserCoords;

            SDL_GetMouseState(&mouseX, &mouseY);
            inUserCoords = fromScreenCoords(point2i(mouseX, mouseY), USER_COORD_CENTER);

            dx = inUserCoords.x - g_endPoint.x;
            dy = inUserCoords.y - g_endPoint.y;
            if ( dx == 0 && dy == 0 ) {
                g_endDir = DEFAULT_END_DIR;
            } else {
                g_endDir = vec2(dx, dy);
                g_endDir.Normalize();
            }
        }

        //Отрисовка
        SDL_FillRect(display, NULL, FILL_COLOR);
            drawEndPoint(display);
            drawEndDir(display);
            drawRobot(display);
            drawPath(display);
        tex = SDL_CreateTextureFromSurface(ren, display);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
        SDL_DestroyTexture(tex);
    }

    SDL_FreeSurface(display);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}