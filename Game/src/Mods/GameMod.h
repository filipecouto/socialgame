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
#include "GameModEventListener.h"

class IPendingGamesList;
class INotificationsList;
class IMoodsList;

class GameMod {
	public:
		virtual void load() { }

		virtual IUser * getIdentity() = 0;

		virtual INotificationsList * getNotifications() = 0;
		
		virtual IMoodsList * getMoods() = 0;

		virtual IPendingGamesList * getPendingGames() = 0;

		virtual void setEventListener(GameModEventListener * listener) = 0;
};

#endif
