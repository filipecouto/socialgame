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
		virtual std::string getName() { }

		virtual Mood getMood() { }

		virtual int getScore() { }

		virtual int getStrength() { }

		virtual std::vector<Tag> getTags() { }

		virtual std::vector<IConnection> getConnections() { }

		virtual ~IPerson() { }
};

#endif
