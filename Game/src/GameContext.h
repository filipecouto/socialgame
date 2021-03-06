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
#include <GL/gl.h>
#include "Models/IPerson.h"

class IMinigameFactory;
class IMinigameInstance;
class IGraphic;
class GraphicFactory;

class GameContext {
	public:
		virtual GraphicFactory * getFactory() = 0;
		virtual IGraphic * getGraphic(IPerson *) = 0;
		
		virtual GLuint loadTexture(std::string texture) = 0;
		
		virtual IMinigameFactory * getMinigameFactory() = 0;
		virtual void notifyMinigameFinished(IMinigameInstance *) = 0;
		
		virtual std::string getString(std::string value) = 0;

		virtual ~GameContext() { }
};

#endif
