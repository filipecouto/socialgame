/*
* User - Header
*
* This code is part of the game module of the Social Game.
*
* CrossWeb Enterprise - 2013
*/

#ifndef SM_USER_H
#define SM_USER_H

#include "../../Models/IUser.h"
#include "Person.h"

class User : public IUser {
public:
	virtual IPerson * getPerson();
	virtual void addFriend(IPerson * friendToAdd);
	virtual ~User();

private:
	Person player;
};

#endif // USER_H
