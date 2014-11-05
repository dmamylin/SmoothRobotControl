#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "utilities.h"

double dotProduct(const vec2& v1, const vec2& v2) {
    return v1.x*v2.x + v1.y*v2.y;
}

/*На входе:
    r, theta, delta - те же, что рассчитываются в функции step и
    maxVelocity - верхняя граница линейной скорости
    k - положительный коэффициент. Подбирать опытным путем. ВРЕМЕННОЕ РЕШЕНИЕ!
На выходе:
    линейная скорость*/
double getLinearVelocity_simple(double r, double theta, double delta, double maxVelocity, double k) {
    return k * r; //ВРЕМЕННОЕ РЕШЕНИЕ!
}

/*На входе:
    r, theta, delta - те же, что рассчитываются в функции step и
    maxVelocity - верхняя граница линейной скорости
    lambda, beta, k1, k2 - положительные константы
На выходе:
    линейная скорость*/
double getLinearVelocity_curvature(double r, double theta, double delta, double lambda, double beta, double maxVelocity, double k1, double k2) {
    double curvature = -(1.0 / r) * (k2*(delta - atan(-k1*theta)) + (1 + k1/(1+k1*k1*theta*theta))*sin(delta));
    return maxVelocity / (1 + beta*pow(abs(curvature), lambda));
}

/*На входе:
    rPos - координаты робота
    tPos - координаты цели

    rDir - ненулевой вектор направления робота
    tDir - ненулевой вектор направления при достижении цели

    backward - флаг движения: false - передом, true - задом. По умолчанию передом.
На выходе:
    Двумерный вектор вида: (угловая скорость, линейная скорость)
*/
vec2 step(const vec2& rPos, const vec2& tPos, const vec2& rDir, const vec2& tDir, bool backward = false) {
    /*r - расстояние от робота до цели
    dir - вектор направления на цель. По совместительству - направляющий вектор полярной оси
    normal - нормальный вектор к вектору dir
    delta - угол между rDir и dir; значения: (-Pi, Pi] отн. полярной оси
    theta - угол между tDir и dir; значения: (-Pi, Pi] отн. полярной оси
    linVel - линейная скорость. Для асимпт. уст. необходимо и достаточно, чтобы linVel -> 0 при r -> 0
    angVel - угловая скорость
    cosTheta, cosDelta - косинусы углов тета и дельта соответственно.*/
    double r, delta, theta, linVel, angVel;
    vec2 dir = tPos - rPos;
    vec2 normal(-dir.y, dir.x);
    vec2 robotDir = backward ? -rDir : rDir;
    double cosTheta, cosDelta;

	//"Хорошие" значения: k1 = 1.0, k2 = 10.0, beta = 0.4, lambda = 2.0
	//Уменьшая k1, можно спрямить траекторию
    const double k1 = .1; //TODO: убрать все в параметры
    const double k2 = 10.0;
    const double beta = 0.4;
    const double lambda = 2.0;
    const double maxVelocity = 4.0;

    //Косинусы получаем из скалярного произведения:
    cosTheta = dotProduct(dir, tDir) / (dir.Length() * tDir.Length());
    cosDelta = dotProduct(dir, robotDir) / (dir.Length() * robotDir.Length());

    //Получим модули углов:
    theta = acos(cosTheta);
    delta = acos(cosDelta);

    //Теперь определим знаки из общего уравнения прямой, соответствующей полярной оси:
    theta = dotProduct(tDir, normal) >= 0 ? theta : -theta;
    delta = dotProduct(robotDir, normal) >= 0 ? delta : -delta;

    //r - просто длина вектора dir
    r = rPos == tPos ? 0.0 : dir.Length(); //TODO: сделать сравнение с точностью

    linVel = getLinearVelocity_curvature(r, theta, delta, lambda, beta, maxVelocity, k1, k2);
    linVel = backward ? -linVel : linVel;

    //Максимальное значение угловой скорости = maxVelocity * Pi / 4
    angVel = (-linVel / r) * (k2*(delta - atan(-k1*theta)) + (1 + k1/(1 + k1*k1*theta*theta))*sin(delta));
    angVel = backward ? -angVel : angVel;

    return vec2(angVel, linVel);
}

#endif