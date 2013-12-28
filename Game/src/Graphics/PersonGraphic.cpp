/*
 * PersonGraphic - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "PersonGraphic.h"
#include "GraphicFactory.h"

PersonGraphic::PersonGraphic(IPerson * person) : PersonGraphic(person, 0) {
}
PersonGraphic::PersonGraphic(IPerson * person, GLfloat startAngle) : _person(person), _startAngle(startAngle) {
	radius = 1.0 + _person->getTags().size() * 0.4;
}

void PersonGraphic::load(GameContext * context) {
	int len = _person->getConnections().size();

	for (int i = 0; i < len; i++) {
		IConnection * connection = _person->getConnections()[i];
		ConnectionGraphic * c = (ConnectionGraphic *) context->getFactory()->build(connection);
		children.push_back(c);
		PersonGraphic * pointingTo = (PersonGraphic *) context->getGraphic(connection->getPerson());
		c->pointTo(pointingTo->x - x, pointingTo->y - y, pointingTo->z - z);
	}
}

void PersonGraphic::draw() {
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f((_person->getName()[0] - 'A') / 26.0f, (_person->getName()[1] - 'a') / 26.0f, (_person->getName()[2] - 'a') / 26.0f);
	glutSolidSphere(radius, 24, 24);
	glColor3f(1, 1, 1);

	int len = children.size();

	for (int i = 0; i < len; i++) {
		children[i]->draw();
	}

	glPopMatrix();
}

void PersonGraphic::drawPickMode() {
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidSphere(radius, 24, 24);

	int len = children.size();

	for (int i = 0; i < len; i++) {
		glPushName(i);
		children[i]->drawPickMode();
		glPopName();
	}

	glPopMatrix();
}

IPerson * PersonGraphic::getPerson() {
	return _person;
}

GLdouble PersonGraphic::getRadius() {
	return radius;
}

bool PersonGraphic::operator==(IPerson * person) {
	return _person == person;
}

PersonGraphic::~PersonGraphic() {

}
