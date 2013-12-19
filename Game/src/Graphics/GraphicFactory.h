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
#include "../Models/IPerson.h"
#include "../Models/IConnection.h"
#include "../Models/Tag.h"

/**
 * This factory will create IGraphic's based on the object it gets
 */
class GraphicFactory {
	public:
		GraphicFactory() {
		}

		IGraphic * build(IPerson * person) {
			return new PersonGraphic(person);
		}
		IGraphic * build(IConnection * connection) {
			return new ConnectionGraphic(connection);
		}
		IGraphic * build(Tag * tag) {
			return NULL;
		}
};

#endif
