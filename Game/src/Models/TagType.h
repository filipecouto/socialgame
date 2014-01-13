/**
* TagType - Header
*
* This code is part of the game module of the Social Game.
*
* CrossWeb Enterprise - 2013
*/

#ifndef TAGTYPE_H
#define TAGTYPE_H

#include <string>

class TagType {
public:
	TagType();
	TagType(std::string description);

	std::string getDescription();
	void setDescription(std::string description);

	virtual ~TagType();

private:
	std::string _description;
};

#endif
