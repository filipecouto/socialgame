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
#include "Person.h"

class Connection : public IConnection {
	public:
		Connection();
		Connection(Person * p);

		virtual std::vector< Tag * > getTags();
		virtual int getScore();
		virtual int getStrength();
		virtual int getState();
		virtual IPerson * getPerson();

		virtual ~Connection();

	private:
		Person * _p = NULL;
};

#endif // CONNECTION_H
