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
// 	animate(tex, cex, tey, cey, tez, cez);
// 	animate(tcx, ccx, tcy, ccy, tcz, ccz);
// 	//animate(tux, cux, tuy, cuy, tuz, cuz);
// 	cux = 0;
// 	cuy = 1;
// 	cuz = 0;
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
		printf("ccx = %.4f\tccy = %.4f\tccz = %.4f\n\n", ccx, ccy, ccz);
		angle += y;
		double n = sqrt(ccx * ccx + ccz * ccz);
		tcx = sin(angle) * n + cex;
		tcz = cos(angle) * n + cez;
		printf("tcx = %.4f\ttcy = %.4f\ttcz = %.4f\tn = %.4f\n", tcx, tcy, tcz, n);
	} else if (z != 0) { // rotation on Z axis
	}
}

void Camera::translateToCamera() {
	glTranslatef(cex, cey, cez);
}

void Camera::animate(GLfloat target, GLfloat & value) {
	//value += (target - value) * 0.04f;
	value = target;
}

// void Camera::animate(GLfloat tx, GLfloat & cx, GLfloat ty, GLfloat & cy, GLfloat tz, GLfloat & cz) {
// 	GLfloat n = sqrt(cx * cx + cy * cy + cz * cz);
// 	GLfloat tmx = cx + (tx - cx) * .04f;
// 	GLfloat tmy = cy + (ty - cy) * .04f;
// 	GLfloat tmz = cz + (tz - cz) * .04f;
// 	GLfloat tn = sqrt(tmx * tmx + tmy * tmy + tmz * tmz);
// 
// 	if (tn == 0 || n == 0) {
// 		cx = tmx;
// 		cy = tmy;
// 		cz = tmz;
// 	} else {
// 		cx = tmx * n / tn;
// 		cy = tmy * n / tn;
// 		cz = tmz * n / tn;
// 	}
// }

GLfloat Camera::getY() {
	return cey;
}

Camera::~Camera() {

}
