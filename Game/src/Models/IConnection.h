/**
* IConnection - Header
*
* This code is part of the game module of the Social Game.
*
* CrossWeb Enterprise - 2013
*/

#ifndef ICONNECTION_H
#define ICONNECTION_H

#include <string>
#include <vector>

#include "Tag.h"
#include "IPerson.h"

class IPerson;

class IConnection {
	public:
		virtual IPerson * getPerson() = 0;

		virtual int getState() = 0;
		
		virtual int getStrength() = 0;

		virtual int getScore() = 0;

		virtual std::vector<Tag*> getTags() = 0;

		virtual ~IConnection() { }
};

#endif
