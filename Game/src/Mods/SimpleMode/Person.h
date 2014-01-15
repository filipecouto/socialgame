/*
 * Person - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 *
 */

#ifndef SM_PERSON_H
#define SM_PERSON_H

#include "../../Models/IPerson.h"
#include "../../Models/IConnectionsList.h"



namespace SimpleMode {
	class Mood;
	class ConnectionsList;
	class Person : public IPerson {
		public:
			virtual ITagsList * getTags();
			Person(std::string name, IMood * mood);
			virtual std::string getName();
			virtual IMood * getMood();
			virtual int getScore();
			virtual int getStrength();
			virtual IConnectionsList * getConnections();
			virtual void connect(Person * other);
			virtual ~Person();
		private:
			ConnectionsList * _connections = NULL;
			std::string name;
			IMood * mood;
	};
}

#endif // PERSON_H
