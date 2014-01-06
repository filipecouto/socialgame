/**
* SimpleMode - Header
*
* This code is part of the game module of the Social Game.
*
* CrossWeb Enterprise - 2013
*/

#ifndef SIMPLEMODE_H
#define SIMPLEMODE_H

#include "../GameMod.h"

class SimpleMode : public GameMod {
	public:

		SimpleMode();
		~SimpleMode();

		virtual void load();

		virtual IUser * getIdentity();
		virtual std::vector<INotification *> * getNotifications();
		virtual void * getPendingGames();

		virtual void setEventListener(GameModEventListener * listener);


private:
	User user;
	GameModEventListener * _listener;

};
#endif