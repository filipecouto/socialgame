/**
* Mood - Implementation
*
* This code is part of the game module of the Social Game.
*
* CrossWeb Enterprise - 2013
*/

#include "Mood.h"

Mood::Mood() {

}


std::string Mood::getDescription() {
	return _description;
}

void Mood::setDescription(std::string description) {
	_description = description;
}

Mood::~Mood() {

}
