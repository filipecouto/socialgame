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
#include "../GameModEventListener.h"




namespace SimpleMode {
	class Person;
	class User : public IUser {
		public:
			User();
			virtual IPerson * getPerson();
			virtual void addFriend(IPerson * friendToAdd);
			virtual void removeFriend(IPerson * friendToRemove);
			virtual void setMood(IMood * mood);
			virtual void setTags(std::vector< std::string > tags);
			virtual void addFriend(Person * friendToAdd);
			virtual ~User();
			virtual void setEventListener(GameModEventListener * listener);
		private:
			Person * player = NULL;
			GameModEventListener * _listener;
	};
}

#endif // USER_H
