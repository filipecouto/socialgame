/**
 * GameMod - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef GAMEMOD_H
#define GAMEMOD_H

#include "../Models/Person.h"

class GameMod {
	public:
		virtual void load();
		
		virtual IPerson * getIdentity();
		
		// TODO interface missing
		virtual void * getNotifications();
		
		// TODO interface missing
		virtual void * getPendingGames();

	private:
		
};

#endif