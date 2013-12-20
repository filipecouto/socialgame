/*
 * PersonGraphic - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "PersonGraphic.h"
#include "GraphicFactory.h"

#include <GL/freeglut.h>

PersonGraphic::PersonGraphic(IPerson * person) {
	_person = person;
	
	load();
}

void PersonGraphic::load() {
	GraphicFactory factory;
	int len = _person->getConnections().size();

	for (int i = 0; i < len; i++) {
		children.push_back(factory.build(_person->getConnections()[i]));
	}
}

void PersonGraphic::draw() {
	glPushMatrix();
	glutSolidSphere(1, 24, 24);
	
	int len = children.size();

	for (int i = 0; i < len; i++) {
		children[i]->draw();
		glRotatef(360/len, 0, 1, 0);
	}

	glPopMatrix();
}

PersonGraphic::~PersonGraphic() {

}
