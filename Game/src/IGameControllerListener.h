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

class IGraphic;

class IGameControllerListener {
	public:
		virtual void onPersonClicked(IPerson * person) { }

		virtual ~IGameControllerListener() { }
};

#endif
