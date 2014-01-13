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

#include "ITag.h"
#include "IPerson.h"

class ITagsList;
class IPerson;

class IConnection {
	public:
		virtual IPerson * getPerson() = 0;

		virtual int getState() = 0;
		
		virtual int getStrength() = 0;

		virtual int getScore() = 0;

		virtual ITagsList * getTags() = 0; // TODO make it abstract once all mods support it

		virtual ~IConnection() { }
};

#endif
