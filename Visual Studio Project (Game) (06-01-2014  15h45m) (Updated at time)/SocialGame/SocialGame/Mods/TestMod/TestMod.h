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
#include "../GameModEventListener.h"
#include "User.h"

class TestMod : public GameMod {
	public:
		TestMod();
		
		virtual void load();
		
		virtual IUser * getIdentity();
		virtual std::vector<INotification *> * getNotifications();
		virtual void * getPendingGames();
		
		virtual void setEventListener(GameModEventListener * listener);
		
		~TestMod();
	private:
		User user;
		GameModEventListener * _listener;
};

#endif // TESTMOD_H
