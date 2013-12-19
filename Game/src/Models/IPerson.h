/**
* IPerson - Header
*
* This code is part of the game module of the Social Game.
*
* CrossWeb Enterprise - 2013
*/

#ifndef IPERSON_H
#define IPERSON_H

#include <string>
#include <vector>
#include "IConnection.h"
#include "Mood.h"
#include "Tag.h"

class IPerson {
	public:
		virtual std::string getName() = 0;

		virtual Mood getMood() = 0;

		virtual int getScore() = 0;

		virtual int getStrength() = 0;

		virtual std::vector<Tag*> getTags() = 0;

		virtual std::vector<IConnection*> getConnections() = 0;

		virtual ~IPerson(){}
};

#endif
