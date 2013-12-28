/*
 * Camera - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "Camera.h"

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
	tcx += x;
	tcy += y;
	tcz += z;
	tex += x;
	tey += y;
	tez += z;
}

void Camera::animate(GLfloat target, GLfloat & value) {
	value += (target - value) * 0.04f;
}

Camera::~Camera() {

}
