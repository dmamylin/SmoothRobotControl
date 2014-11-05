#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "utilities.h"

double dotProduct(const vec2& v1, const vec2& v2) {
    return v1.x*v2.x + v1.y*v2.y;
}

/*�� �����:
    r, theta, delta - �� ��, ��� �������������� � ������� step �
    maxVelocity - ������� ������� �������� ��������
    k - ������������� �����������. ��������� ������� �����. ��������� �������!
�� ������:
    �������� ��������*/
double getLinearVelocity_simple(double r, double theta, double delta, double maxVelocity, double k) {
    return k * r; //��������� �������!
}

/*�� �����:
    r, theta, delta - �� ��, ��� �������������� � ������� step �
    maxVelocity - ������� ������� �������� ��������
    lambda, beta, k1, k2 - ������������� ���������
�� ������:
    �������� ��������*/
double getLinearVelocity_curvature(double r, double theta, double delta, double lambda, double beta, double maxVelocity, double k1, double k2) {
    double curvature = -(1.0 / r) * (k2*(delta - atan(-k1*theta)) + (1 + k1/(1+k1*k1*theta*theta))*sin(delta));
    return maxVelocity / (1 + beta*pow(abs(curvature), lambda));
}

/*�� �����:
    rPos - ���������� ������
    tPos - ���������� ����

    rDir - ��������� ������ ����������� ������
    tDir - ��������� ������ ����������� ��� ���������� ����

    backward - ���� ��������: false - �������, true - �����. �� ��������� �������.
�� ������:
    ��������� ������ ����: (������� ��������, �������� ��������)
*/
vec2 step(const vec2& rPos, const vec2& tPos, const vec2& rDir, const vec2& tDir, bool backward = false) {
    /*r - ���������� �� ������ �� ����
    dir - ������ ����������� �� ����. �� ���������������� - ������������ ������ �������� ���
    normal - ���������� ������ � ������� dir
    delta - ���� ����� rDir � dir; ��������: (-Pi, Pi] ���. �������� ���
    theta - ���� ����� tDir � dir; ��������: (-Pi, Pi] ���. �������� ���
    linVel - �������� ��������. ��� ������. ���. ���������� � ����������, ����� linVel -> 0 ��� r -> 0
    angVel - ������� ��������
    cosTheta, cosDelta - �������� ����� ���� � ������ ��������������.*/
    double r, delta, theta, linVel, angVel;
    vec2 dir = tPos - rPos;
    vec2 normal(-dir.y, dir.x);
    vec2 robotDir = backward ? -rDir : rDir;
    double cosTheta, cosDelta;

	//"�������" ��������: k1 = 1.0, k2 = 10.0, beta = 0.4, lambda = 2.0
	//�������� k1, ����� �������� ����������
    const double k1 = .1; //TODO: ������ ��� � ���������
    const double k2 = 10.0;
    const double beta = 0.4;
    const double lambda = 2.0;
    const double maxVelocity = 4.0;

    //�������� �������� �� ���������� ������������:
    cosTheta = dotProduct(dir, tDir) / (dir.Length() * tDir.Length());
    cosDelta = dotProduct(dir, robotDir) / (dir.Length() * robotDir.Length());

    //������� ������ �����:
    theta = acos(cosTheta);
    delta = acos(cosDelta);

    //������ ��������� ����� �� ������ ��������� ������, ��������������� �������� ���:
    theta = dotProduct(tDir, normal) >= 0 ? theta : -theta;
    delta = dotProduct(robotDir, normal) >= 0 ? delta : -delta;

    //r - ������ ����� ������� dir
    r = rPos == tPos ? 0.0 : dir.Length(); //TODO: ������� ��������� � ���������

    linVel = getLinearVelocity_curvature(r, theta, delta, lambda, beta, maxVelocity, k1, k2);
    linVel = backward ? -linVel : linVel;

    //������������ �������� ������� �������� = maxVelocity * Pi / 4
    angVel = (-linVel / r) * (k2*(delta - atan(-k1*theta)) + (1 + k1/(1 + k1*k1*theta*theta))*sin(delta));
    angVel = backward ? -angVel : angVel;

    return vec2(angVel, linVel);
}

#endif