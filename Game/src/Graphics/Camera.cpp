/*
 * Camera - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "Camera.h"

Camera::Camera() {
	tex = -1;
	tey = 0;
	tez = 0;
	tcx = 2;
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
		tey = -2;
	} else if (currentType == FirstPerson) {
		tey = 2;
	} else  {
		tey = 0;
	}
}

void Camera::tick(GLfloat delta, GLfloat absolute) {
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

void Camera::animate(GLfloat target, GLfloat & value) {
	value += (target - value) * 0.05f;
}

Camera::~Camera() {

}
