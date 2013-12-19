/*
 * ConnectionGraphic - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef CONNECTIONGRAPHIC_H
#define CONNECTIONGRAPHIC_H

#include "IGraphic.h"
#include "../Models/IConnection.h"

class ConnectionGraphic : public IGraphic {
	public:
		ConnectionGraphic(IConnection * connection);
		
		virtual void draw();
		
		~ConnectionGraphic();
};

#endif // CONNECTIONGRAPHIC_H
