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
#include "../Models/IPerson.h"
#include "../GameContext.h"
#include <GL/freeglut.h>

class PersonGraphic : public IGraphic {
	public:
		PersonGraphic(IPerson * person);
		PersonGraphic(IPerson * person, GLfloat startAngle);
		
		virtual void load(GameContext * context);
		virtual void draw();
		
		virtual bool operator==(IPerson * person);
		
		GLfloat x = 0, y = 0, z = 0;

		~PersonGraphic();

	private:
		IPerson * _person = NULL;
		GLfloat _startAngle;

		std::vector<IGraphic *> children;
		
		GLdouble radius;
};

#endif // PERSONGRAPHIC_H
