/*
 * ConnectionGraphic - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "ConnectionGraphic.h"

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

#define TODEGREES(rad) rad*180/M_PI

ConnectionGraphic::ConnectionGraphic(IConnection * connection) : _connection(connection) {

}

ConnectionGraphic::ConnectionGraphic(IConnection * connection, GLfloat angle) : _connection(connection) {
}

void ConnectionGraphic::load(GameContext * context) {
	mode = _connection->getState();
}

void ConnectionGraphic::pointTo(GLfloat x, GLfloat y, GLfloat z) {
	_length = sqrt(x * x + y * y + z * z);

	_angle[0] = 0;
	_angle[1] = -(z == 0 ? (y == 0 ? 0 : (y > 0 ? 90 : -90)) : ((z < 0 ? 180 : 0) + TODEGREES(atan(y / z))));
	_angle[2] = TODEGREES(asin(x / _length));

	printf("Pointing to (%f, %f, %f)...\n\tGoing to rotate: %fº, %fº, %fº\n", x, y, z, _angle[0], _angle[1], _angle[2]);
}

void ConnectionGraphic::draw() {
	glPushMatrix();

	glRotatef(_angle[1], 1, 0, 0);
	glRotatef(_angle[2], 0, 1, 0);

	if (mode == 0) {
		glColor3f(0.5f, 0.5f, 0.5f);

		glutSolidCylinder(0.25f, _length / 3, 16, 8);
		glTranslatef(0, 0, 2 * _length / 3);
		glutSolidCylinder(0.25f, _length / 3, 16, 8);
	} else {
		if (mode == 1)
			glColor3f(0.9f, 1.0f, 0.9f);
		else if (mode == -1)
			glColor3f(0.9f, 0.1f, 0.1f);

		glutSolidCylinder(0.25f, _length, 16, 8);
	}

	glPopMatrix();
}

IConnection * ConnectionGraphic::getConnection() {
	return _connection;
}

ConnectionGraphic::~ConnectionGraphic() {

}
