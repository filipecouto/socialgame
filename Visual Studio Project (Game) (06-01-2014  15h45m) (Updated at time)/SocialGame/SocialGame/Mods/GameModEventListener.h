/**
 * GameModEventListener - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef GAMEMODEVENTLISTENER_H
#define GAMEMODEVENTLISTENER_H

#include "../Models/INotification.h"

class GameModEventListener {
	public:
		virtual void onNewNotification(INotification * notification) = 0;
};

#endif
