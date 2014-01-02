/**
 * GraphicFactory - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef GRAPHICFACTORY_H
#define GRAPHICFACTORY_H

#include "IGraphic.h"
#include "PersonGraphic.h"
#include "ConnectionGraphic.h"

class IPerson;
class IConnection;
class Tag;

/**
 * This factory will create IGraphic's based on the object it gets
 */
class GraphicFactory {
	public:
		GraphicFactory() {
		}

		IGraphic * build(IPerson * person);
		IGraphic * build(IPerson * person, GLfloat angle);

		IGraphic * build(IConnection * connection);
		IGraphic * build(IConnection * connection, GLfloat angle);

		IGraphic * build(Tag * tag);
};

#endif
