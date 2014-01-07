/**
 * GameMod - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef GAMEMOD_H
#define GAMEMOD_H

#include "../Models/IUser.h"
#include "../Models/INotification.h"
#include "GameModEventListener.h"

class GameMod {
	public:
		virtual void load() { }

		virtual IUser * getIdentity() = 0;

		virtual std::vector<INotification *> * getNotifications() = 0;

		// TODO interface missing
		virtual void * getPendingGames() = 0;

		virtual void setEventListener(GameModEventListener * listener) { }
};

#endif
