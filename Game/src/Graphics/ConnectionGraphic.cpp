/*
 * ConnectionGraphic - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "ConnectionGraphic.h"

#include <math.h>

#ifndef PI
#define PI 3.14159265359
#endif
#define TODEGREES(rad) rad*180/PI

ConnectionGraphic::ConnectionGraphic(IConnection * connection) {

}

ConnectionGraphic::ConnectionGraphic(IConnection * connection, GLfloat angle) : _connection(connection) {
}

void ConnectionGraphic::pointTo(GLfloat x, GLfloat y, GLfloat z) {
	_length = sqrt(x * x + y * y + z * z);

	_angle[0] = 0;
	GLfloat R = _length;
	_angle[1] = -(z == 0 ? (y == 0 ? 0 : (y > 0 ? 90 : -90)) : ((z < 0 ? 180 : 0) + TODEGREES(atan(y / z))));
	_angle[2] = TODEGREES(asin(x/R));

	printf("Pointing to (%f, %f, %f)...\n\tGoing to rotate: %fº, %fº, %fº\n", x, y, z, _angle[0], _angle[1], _angle[2]);
}

void ConnectionGraphic::draw() {
	glPushMatrix();
	
	glRotatef(_angle[1], 1, 0, 0);
	glRotatef(_angle[2], 0, 1, 0);

	glutSolidCylinder(0.25f, _length, 16, 8);

	glPopMatrix();
}

ConnectionGraphic::~ConnectionGraphic() {

}
