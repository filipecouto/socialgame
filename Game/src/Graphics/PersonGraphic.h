/*
 * PersonGraphic - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef PERSONGRAPHIC_H
#define PERSONGRAPHIC_H

#include "IGraphic.h"
#include "ConnectionGraphic.h"
#include "../Models/IPerson.h"
#include "../GameContext.h"

#include <GL/freeglut.h>

class GraphicFactory;

class PersonGraphic : public IGraphic {
	public:
		PersonGraphic(IPerson * person);
		PersonGraphic(IPerson * person, GLfloat startAngle);
		
		virtual void load(GameContext * context);
		
		virtual void draw();
		virtual void drawPickMode();
		
		void invalidate(IPerson * person);
		
		virtual bool operator==(IPerson * person);
		
		IPerson * getPerson();
		
		GLfloat x = 0, y = 0, z = 0;
		GLdouble getRadius();

		~PersonGraphic();

	private:
		GameContext * _context;
		
		IPerson * _person = NULL;
		GLfloat _startAngle;

		std::vector<ConnectionGraphic *> children;
		void createConnection(IConnection * connection);
		ConnectionGraphic * getConnection(IConnection * connection);
		
		GLdouble radius;
};

#endif // PERSONGRAPHIC_H
