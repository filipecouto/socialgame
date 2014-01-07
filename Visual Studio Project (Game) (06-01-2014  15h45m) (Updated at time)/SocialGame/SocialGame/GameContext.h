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
#include "Models/IPerson.h"

class IMinigameInstance;
class IGraphic;
class GraphicFactory;

class GameContext {
	public:
		virtual GraphicFactory * getFactory() = 0;
		virtual IGraphic * getGraphic(IPerson *) = 0;
		
		virtual void notifyMinigameFinished(IMinigameInstance *) = 0;

		virtual ~GameContext() { }
};

#endif
