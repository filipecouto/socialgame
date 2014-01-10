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
#include "IMood.h"
#include "Tag.h"

class ITagsList;
class IConnection;
class IConnectionsList;

class IPerson {
	public:
		virtual std::string getName() = 0;

		virtual IMood * getMood() = 0;

		virtual int getScore() = 0;

		virtual int getStrength() = 0;

		virtual ITagsList * getTags() { }; // TODO make it abstract once all mods support it

		virtual IConnectionsList * getConnections() = 0;

		virtual ~IPerson() {}
};

#endif
