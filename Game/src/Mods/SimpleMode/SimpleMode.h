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