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

class PersonGraphic : public IGraphic {
	public:
		PersonGraphic(IPerson * person);
		
		void load();
		virtual void draw();

		~PersonGraphic();

	private:
		IPerson * _person = NULL;

		std::vector<IGraphic *> children;
};

#endif // PERSONGRAPHIC_H
