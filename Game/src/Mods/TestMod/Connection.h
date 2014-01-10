/*
 * Connection - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include "../../Models/IConnection.h"

class Person;

class Connection : public IConnection {
	public:
// 		Connection();
		Connection(Person * p);
		Connection(Person * p, int state);

		virtual ITagsList * getTags();
		
		virtual int getScore();
		
		virtual int getStrength();
		
		virtual int getState();
		void setState(int state);
		
		virtual IPerson * getPerson();

		virtual ~Connection();

	private:
		Person * _p = NULL;
		
		int _state;
};

#endif // CONNECTION_H
