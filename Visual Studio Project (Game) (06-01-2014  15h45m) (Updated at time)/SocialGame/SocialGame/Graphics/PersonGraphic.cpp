/*
 * PersonGraphic - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "PersonGraphic.h"
#include "../Models/IConnectionsList.h"
#include "GraphicFactory.h"

PersonGraphic::PersonGraphic(IPerson * person) : PersonGraphic(person, 0) {
}
PersonGraphic::PersonGraphic(IPerson * person, GLfloat startAngle) : _person(person), _startAngle(startAngle) {
	radius = 1.0 + _person->getTags().size() * 0.4;
}

void PersonGraphic::load(GameContext * context) {
	_context = context;

	IConnectionsList * conns = _person->getConnections();
	int len = conns->size();

	for (int i = 0; i < len; i++) {
		IConnection * connection = (*conns)[i];
		createConnection(connection);
	}
}

void PersonGraphic::invalidate(IPerson * person) {
	if (_person == person) {
		IConnectionsList * conns = _person->getConnections();
		int len = conns->size();

		for (int i = 0; i < len; i++) {
			IConnection * connection = (*conns)[i];
			ConnectionGraphic * g = getConnection(connection);

			if (g) {
				PersonGraphic * pointingTo = (PersonGraphic *) _context->getGraphic(connection->getPerson());
				g->pointTo(pointingTo->x - x, pointingTo->y - y, pointingTo->z - z);
			} else {
				// connection is still not represented, let's create it
				createConnection(connection);
			}

			// TODO remove old connections
		}
	} else {
		IConnection * conn = NULL;
		IConnectionsList * conns = _person->getConnections();
		int len = conns->size();

		for (int i = 0; i < len; i++) {
			IConnection * connection = (*conns)[i];

			if (connection && connection->getPerson() == person) {
				conn = connection;
				ConnectionGraphic * g = getConnection(connection);

				if (g) {
					PersonGraphic * pointingTo = (PersonGraphic *) _context->getGraphic(connection->getPerson());
					g->pointTo(pointingTo->x - x, pointingTo->y - y, pointingTo->z - z);
					return;
				}
			}
		}

		// couldn't find it, let's create it
		if (conn) createConnection(conn);
	}
}

void PersonGraphic::createConnection(IConnection * connection) {
	ConnectionGraphic * c = (ConnectionGraphic *) _context->getFactory()->build(connection);
	c->load(_context);
	children.push_back(c);
	PersonGraphic * pointingTo = (PersonGraphic *) _context->getGraphic(connection->getPerson());
	c->pointTo(pointingTo->x - x, pointingTo->y - y, pointingTo->z - z);
}

ConnectionGraphic * PersonGraphic::getConnection(IConnection * connection) {
	for (int i = 0; i < children.size(); i++) {
		ConnectionGraphic * g = children[i];

		if (g->getConnection() == connection) return g;
	}

	return NULL;
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
