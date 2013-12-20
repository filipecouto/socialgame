/*
 * ConnectionGraphic - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "ConnectionGraphic.h"
#include "GraphicFactory.h"

#include <GL/freeglut.h>
#include <cstdio>
ConnectionGraphic::ConnectionGraphic(IConnection * connection) {
	GraphicFactory * factory = new GraphicFactory();
	if(connection->getPerson()) {
		_end = factory->build(connection->getPerson());
	}
}

void ConnectionGraphic::draw() {
	glPushMatrix();
		glutSolidCylinder(0.5f, 4, 16, 8);
		if(_end) {
			glTranslatef(0, 0, 4);
			_end->draw();
		}
	glPopMatrix();
}

ConnectionGraphic::~ConnectionGraphic() {

}
