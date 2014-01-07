/**
 * GraphicFactory - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "GraphicFactory.h"

IGraphic * GraphicFactory::build(IPerson * person) {
	return new PersonGraphic(person);
}

IGraphic * GraphicFactory::build(IPerson * person, GLfloat angle) {
	return new PersonGraphic(person, angle);
}

IGraphic * GraphicFactory::build(IConnection * connection) {
	return new ConnectionGraphic(connection);
}

IGraphic * GraphicFactory::build(IConnection * connection, GLfloat angle) {
	return new ConnectionGraphic(connection, angle);
}

IGraphic * GraphicFactory::build(Tag * tag) {
	return NULL;
}