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
#include <GL/freeglut.h>

class ConnectionGraphic : public IGraphic {
	public:
		ConnectionGraphic(IConnection * connection);
		ConnectionGraphic(IConnection * connection, GLfloat angle);
		
		virtual void draw();
		void pointTo(GLfloat x, GLfloat y, GLfloat z);
		
		~ConnectionGraphic();

	private:
		IConnection * _connection = NULL;
		IGraphic * _end = NULL;
		//GLfloat _angle;
		GLfloat _angle[3];
		GLfloat _length;
};

#endif // CONNECTIONGRAPHIC_H
