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
#include "IPerson.h"

class IConnection {
	public:
		virtual IPerson getPerson();
		virtual void setPerson(IPerson person);

		virtual int getState();
		virtual void setState(int state);
		
		virtual int getStrength();
		virtual void setStrength(int strength);

		virtual int getScore();
		virtual void setScore(int score);

		virtual std::vector<Tag> getTagList();
		virtual void addTag(Tag tag) { }
		virtual void removeTag(Tag tag) { }

		virtual ~IConnection();
};

#endif
