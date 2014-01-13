/*
 * Camera - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "Camera.h"
#include <GL/gl.h>
#include <cmath>
#include <stdio.h>

Camera::Camera() {
	tex = -2;
	tey = 0;
	tez = -2;
	tcx = 0;
	tcy = 0;
	tcz = 0;
	tux = 0;
	tuy = 1;
	tuz = 0;
}

void Camera::setUp() {
	gluLookAt(cex, cey, cez, ccx, ccy, ccz, cux, cuy, cuz);
}

CameraTypes Camera::getType() {
	return currentType;
}

void Camera::setType(CameraTypes type) {
	currentType = type;

	if (currentType == FreeMode) {
		tex = -8;
		tey = 8;
		tez = 0;
	} else if (currentType == FirstPerson) {
		tex = -3;
		tey = 0;
		tez = 3;
		tcx = 0;
		tcy = 0;
		tcz = 0;
	} else {
		tex = 4;
		tey = 0;
		tez = 2;
		tcx = 0;
		tcy = 0;
		tcz = 0;
	}
}

void Camera::tick(int delta, int absolute) {
	animate(tex, cex);
	animate(tey, cey);
	animate(tez, cez);
	animate(tcx, ccx);
	animate(tcy, ccy);
	animate(tcz, ccz);
	animate(tux, cux);
	animate(tuy, cuy);
	animate(tuz, cuz);
}

void Camera::lookAt(GLfloat x, GLfloat y, GLfloat z) {
	tcx = x;
	tcy = y;
	tcz = z;
}

void Camera::moveTo(GLfloat x, GLfloat y, GLfloat z) {
	tex = x;
	tey = y;
	tez = z;
}

void Camera::translate(GLfloat x, GLfloat y, GLfloat z) {
	tex += x;
	tey += y;
	tez += z;
	tcx += x;
	tcy += y;
	tcz += z;
}

void Camera::walk(GLfloat x, GLfloat y, GLfloat z) {
	GLfloat angle = getAngle();

	if (x != 0) {
		tcx = ccx + (x * cos(angle));
		tcz = ccz + (x * sin(angle));
		tex = cex + (x * cos(angle));
		tez = cez + (x * sin(angle));
		return;
	}

	if (z != 0) {
		tcx = ccx + (z * sin(angle));
		tcz = ccz + (z * cos(angle));
		tex = cex + (z * sin(angle));
		tez = cez + (z * cos(angle));
		return;
	}

	if (y != 0) {
		tcy += y;
		tey += y;
		return;
	}
}


GLfloat Camera::getAngle() {
	GLfloat dx = cex - ccx;
	GLfloat dz = cez - ccz;

	GLfloat value = dz == 0 ? M_PI / 2 : atan(dx / dz);

	if (dz > 0) value -= M_PI;

	return value;
}

void Camera::rotate(GLfloat x, GLfloat y, GLfloat z) {
	GLfloat angle = getAngle();

	if (x != 0) { // rotation on X axis
	} else if (y != 0) { // rotation on Y axis
		angle += y;
		double n = sqrt(ccx*ccx + ccz*ccz);
		tcx = sin(angle) * n + cex;
		tcz = cos(angle) * n + cez;
	} else if (z != 0) { // rotation on Z axis
	}
}

void Camera::translateToCamera() {
	glTranslatef(cex, cey, cez);
}

void Camera::animate(GLfloat target, GLfloat & value) {
	value += (target - value) * 0.04f;
}

GLfloat Camera::getY() {
	return cey;
}

Camera::~Camera() {

}
