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

class User : public IUser {
	public:
		virtual IPerson * getPerson();
		virtual void addFriend(IPerson * friendToAdd);

	private:
		Person ritinha;
};

#endif // USER_H
