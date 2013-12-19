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

class GameMod {
	public:
		virtual void load() { }
		
		virtual IUser * getIdentity() = 0;
		
		// TODO interface missing
		virtual void * getNotifications() = 0;
		
		// TODO interface missing
		virtual void * getPendingGames() = 0;

	private:
		
};

#endif