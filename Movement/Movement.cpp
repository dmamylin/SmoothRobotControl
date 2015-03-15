#include <SDL2/SDL.h>

#include <stdio.h>
#include <list>
  
#include "utilities.h"
#include "SDL2Device.h"
#include "SDL2PrimitivePainter.h"
#include "SmoothVelocityController.h"
#include "TestVelocityController.h"

#define CAPTION    "Smooth movement"
#define WIDTH      800
#define HEIGHT     600
#define FILL_COLOR ColorRGB(0, 0, 0)

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
        const f64 STOP_WHEN = 0.01; //Условие остановки
        const f64 EPSILON = 4.0; //Точность достижения цели
    //Для отрисовки:
        const f64 END_VEC_LEN = 20.0; //Длина вектора результирующего направления (в пикселях)
        const f64 ROBOT_DIR_LEN = 30.0; //Длина вектора направления робота (в пикселях)
        const s32 END_POINT_W = 8; //Ширина конечной точки (в пикселях)
        const s32 END_POINT_H = 8; //Высота конечной точки (в пикселях)
        const s32 ROBOT_H = 8; //Длина робота (в пикселях)
        const s32 ROBOT_W = 8; //Ширина робота (в пикселях)
        const u32 END_POINT_COLOR = 0x00FF00;
        const u32 ROBOT_COLOR = 0xFF0000;

//runtime global variables
point2i g_endPoint; //Координата конечной точки (в пользовательской СК, в пикселях)
vec2 g_endDir; //Конечное направление. Должен быть единичной длины (в пользовательской СК)
vec2 g_rPos(0.0, 0.0); //Положение робота (в пользовательской СК, в пикселях)
vec2 g_rDir(0.0, 1.0); //Единичный вектор направления робота (в пользовательской СК)
bool g_onTarget;

std::list<point2i> g_path; //Хранит точки пути для отрисовки
std::list<point2vec2> g_targets; //Список целей
SDL2PrimitivePainter g_painter;

void init() {
    g_endPoint = DEFAULT_END_POINT;
    g_endDir = DEFAULT_END_DIR;
    g_onTarget = false;

    g_targets.push_back(point2<vec2>(vec2(-100.0, -100.0), vec2(0.0, -1.0)));
    g_targets.push_back(point2<vec2>(vec2(100.0, -100.0), vec2(0.0, 1.0)));
	g_targets.push_back(point2<vec2>(vec2(100.0, 100.0), vec2(-1.0, 0.0)));
	g_targets.push_back(point2<vec2>(vec2(-100.0, 100.0), vec2(0.0, -1.0)));
	g_targets.push_back(point2<vec2>(vec2(-100.0, -100.0), vec2(1.0, 0.0)));
}

//Временное решение, чтобы не загромождать
#include "DrawFunctions.h"

int main() {
    SDL2Device device;
    bool endPointExists = true;
    bool mousePressed = false;
    IVelocityController *velocity = new TestVelocityController();

    init();
    device.initialize(WIDTH, HEIGHT, CAPTION);

    while (device.isRun()) {
        SDL_Event ev;

        //Обработка событий
        SDL_PollEvent(&ev);
        if (ev.type == SDL_QUIT ||
           (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)) {
            device.stop();
        } else if (ev.type == SDL_MOUSEBUTTONDOWN && !mousePressed) {
            mousePressed = true;
            if (endPointExists) {
                g_endPoint = g_painter.fromScreenCoords(point2i(ev.button.x, ev.button.y), USER_COORD_CENTER);
                endPointExists = false;
            } else {
                s32 dx, dy;
                point2i inUserCoords;

                inUserCoords = g_painter.fromScreenCoords(device.getMousePosition(), USER_COORD_CENTER);

                dx = inUserCoords.x - g_endPoint.x;
                dy = inUserCoords.y - g_endPoint.y;
                if ( dx == 0 && dy == 0 ) {
                    g_endDir = DEFAULT_END_DIR;
                } else {
                    g_endDir = vec2(dx, dy).normalize();
                }
                endPointExists = true;
                g_path.clear();

				g_onTarget = false;
            }
        } else if (ev.type == SDL_MOUSEBUTTONUP) {
            mousePressed = false;
        } else if (ev.type == SDL_KEYDOWN) {
            if (ev.key.keysym.sym == SDLK_SPACE) {
                vec2 endVec = vec2((f64)g_endPoint.x, (f64)g_endPoint.y);
                if ((endVec - g_rPos).length() <= EPSILON) {
					g_onTarget = g_targets.empty() ? true : false;

                    if (!g_onTarget) {
						g_endPoint = point2i(g_targets.front().x);
						g_endDir = g_targets.front().y;
						g_targets.pop_front();
					}
                    endVec = vec2((f64)g_endPoint.x, (f64)g_endPoint.y);
                }

				if (!g_onTarget) {
                    // x - расстояние от робота до цели
                    // y - путевой угол робота (между плярной осью и его направлением)
                    // z - путевой угол цели (между плярной осью и ее направлением)
                    vec3 robotCoordinates = fromGlobalToLocal(g_rPos, endVec,
                        g_rDir, g_endDir);
                    velocity->run(robotCoordinates.x, robotCoordinates.y, robotCoordinates.z);
					g_path.push_back(g_painter.toScreenCoords(point2i((s32)g_rPos.x, (s32)g_rPos.y), USER_COORD_CENTER));

                    g_rDir = rotationMatrix2D(velocity->getAngularVelocity()) * g_rDir;
					g_rDir.normalize();

                    g_rPos += velocity->getLinearVelocity() * g_rDir;
				}
            }
        }

        if ( !endPointExists ) {
            s32 dx, dy;
            point2i inUserCoords;

            inUserCoords = g_painter.fromScreenCoords(device.getMousePosition(), USER_COORD_CENTER);

            dx = inUserCoords.x - g_endPoint.x;
            dy = inUserCoords.y - g_endPoint.y;
            if ( dx == 0 && dy == 0 ) {
                g_endDir = DEFAULT_END_DIR;
            } else {
                g_endDir = vec2(dx, dy).normalize();
            }
        }

        //Отрисовка
        device.beginScene(FILL_COLOR);
            drawEndPoint(device.getDisplaySurface());
            drawEndDir(device.getDisplaySurface());
            drawRobot(device.getDisplaySurface());
            drawPath(device.getDisplaySurface());
        device.endScene();
    }

    delete velocity;
    return 0;
}