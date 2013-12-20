/**
* GameContext - Header
*
* This code is part of the game module of the Social Game.
*
* CrossWeb Enterprise - 2013
*/

#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include <string>
#include <vector>
#include "Graphics/PersonGraphic.h"

class GameContext {
	public:
		virtual PersonGraphic getGraphic(Person*);

		virtual ~GameContext() { }
};

#endif
