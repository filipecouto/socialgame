/*
 * Person - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 *
 */

#ifndef PERSON_H
#define PERSON_H

#include "../../Models/IPerson.h"
#include "../../Models/IConnectionsList.h"
#include "FriendsList.h"

class Person : public IPerson {
	public:
		Person(std::string name, IMood * mood);
		
		virtual std::string getName();
		virtual IMood * getMood();
		virtual int getScore();
		virtual int getStrength();
		
		virtual ITagsList * getTags();
		virtual IConnectionsList* getConnections();
		
		void connect(Person * other);
		IConnection * connect(Person * other, int state);
		
		void test(int n) {
			_test = n;
		}
		
		virtual ~Person();
	private:
		FriendsList* _connections = NULL;
		
		int _test = 0;
		std::string _name;
		IMood * _mood = NULL;
};

#endif // PERSON_H
