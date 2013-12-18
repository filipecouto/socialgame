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
#include "Mood.h"
#include "Tag.h"

class IPerson {
	public:
		virtual std::string getName();
		virtual void setName(std::string name);

		virtual Mood getMood();
		virtual void setMood(Mood mood);

		virtual int getScore();
		virtual void setScore(int score);

		virtual int getStrength();
		virtual void setStrength(int strength);

		virtual std::vector<Tag> getTagList();
		virtual void addTag(Tag tag) { }
		virtual void removeTag(Tag tag) { }

		virtual std::vector<IConnection> getConnectionList();
		virtual void addConnection(IConnection connection) { }
		virtual void removeConnection(IConnection connection) { }

		virtual ~IPerson();
};

#endif
