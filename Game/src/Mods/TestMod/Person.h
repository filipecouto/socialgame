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

class Person : public IPerson {
	public:
		virtual std::string getName();
		virtual Mood getMood();
		virtual int getScore();
		virtual int getStrength();
		virtual std::vector< Tag * > getTags();
		virtual std::vector< IConnection * > getConnections();
		
		void test(int n) {
			_test = n;
		}
		
		virtual ~Person();
	private:
		std::vector<IConnection *> * _connections;
		
		int _test = 0;
};

#endif // PERSON_H
