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

	if(currentType == FreeMode) {
		tex = -8;
		tey = 8;
		tez = 0;
	} else if(currentType == FirstPerson) {
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
	tex+=x;
	tey+=y;
	tez+=z;
	tcx+=x;
	tcy+=y;
	tcz+=z;
}

void Camera::walk(GLfloat x, GLfloat y, GLfloat z) {
	// TODO doesn't behave correctly
	GLfloat angle = getAngle();
	printf("angle = %0.2f\n", angle);
	if(x!=0 || y!=0) {
		GLfloat value = x!=0? x : y;
		tcx = ccx + (value * cos(-angle));
		tcz = ccz + (value * sin(-angle));
		tex = cex + (value * cos(-angle));
		tez = cez + (value * sin(-angle));
		return;
	}
	if(z!=0) {
		tcz += z;
		tez += z;
		return;
	}
}


GLfloat Camera::getAngle() {
	GLfloat dx = cex - ccx;
	GLfloat dy = cey - ccy;
	GLfloat dz = cez - ccz;
	return atan(dx/dz);
}

void Camera::rotate(GLfloat x, GLfloat y, GLfloat z) {
	GLfloat oldAngle = getAngle(), angle;
	if(x != 0) { // rotation on X axis
	} else if(y != 0) { // rotation on Y axis
		angle = oldAngle + y;
		tcz = cos(angle) + tez;
		tcx = sin(angle) + tex;
	} else if(z != 0) { // rotation on Z axis
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
