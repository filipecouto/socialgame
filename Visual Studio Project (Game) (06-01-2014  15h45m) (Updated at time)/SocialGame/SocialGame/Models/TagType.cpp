/**
* TagType - Implementation
*
* This code is part of the game module of the Social Game.
*
* CrossWeb Enterprise - 2013
*/

#include "TagType.h"

TagType::TagType() {

}

TagType::TagType(std::string description) : _description(description) {

}

std::string TagType::getDescription() {
	return _description;
}

void TagType::setDescription(std::string description) {
	_description = description;
}

TagType::~TagType() {

}
