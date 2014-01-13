/**
 * Tag - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "Tag.h"

Tag::Tag() {
	
}

Tag::Tag(std::string name) : _name(name) {
	
}

std::string Tag::getName() {
	return _name;
}

void Tag::setName(std::string name) {
	_name = name;
}

Tag::~Tag() {
	
}
