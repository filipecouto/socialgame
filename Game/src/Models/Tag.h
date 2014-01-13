/**
 * Tag - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef TAG_H
#define TAG_H

#include <string>

class Tag {
	public:
		Tag();
		Tag(std::string name);
		
		std::string getName();
		void setName(std::string name);
		
		virtual ~Tag();

	private:
		std::string _name;
};

#endif
