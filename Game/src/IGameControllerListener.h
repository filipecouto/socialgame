/**
* IGameControllerListener - Header
*
* This code is part of the game module of the Social Game.
*
* CrossWeb Enterprise - 2013
*/

#ifndef IGAMECONTROLLERLISTENER_H
#define IGAMECONTROLLERLISTENER_H

#include <string>
#include <vector>
#include "Models/IPerson.h"
#include "Mods/GameModEventListener.h"

class IMinigameInstance;
class IMinigame;
class IGraphic;

class IGameControllerListener : public GameModEventListener {
	public:
		virtual void onGameLoaded() = 0;
		
		virtual void onPersonClicked(IPerson * person) = 0;
		
		virtual void onMinigameEnded(IMinigameInstance * instance) = 0;
};

#endif
