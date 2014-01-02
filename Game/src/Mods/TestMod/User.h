/*
 * User - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef USER_H
#define USER_H

#include "../../Models/IUser.h"
#include "Person.h"
#include "../GameModEventListener.h"

class User : public IUser {
	public:
		User();
		
		virtual IPerson * getPerson();
		virtual void addFriend(IPerson * friendToAdd);
		
		virtual void setEventListener(GameModEventListener * listener);
		
		virtual ~User();

	private:
		Person ritinha;
		GameModEventListener * _listener;
};

#endif // USER_H
