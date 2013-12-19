/**
 * TestMod - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef TESTMOD_H
#define TESTMOD_H

#include "../GameMod.h"
#include "User.h"

class TestMod : public GameMod {
    public:
		TestMod();
		~TestMod();
		virtual void load();
		virtual IUser* getIdentity();
		virtual void* getNotifications();
		virtual void* getPendingGames();

	private:
		User user;
};

#endif // TESTMOD_H
