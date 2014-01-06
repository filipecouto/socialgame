/*
 * Person - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 *
 */

#include "Person.h"

std::string Person::getName() {
	return "Dummy";
}

Mood * Person::getMood() {
	return new Mood("Neutral");
}

int Person::getScore() {
	return 0;
}

int Person::getStrength() {
	return 0;
}

std::vector<Tag *> Person::getTags(){
	return std::vector<Tag*>();
}

std::vector< IConnection * > Person::getConnections() {
	if(_connections == NULL) {
		_connections = new std::vector<IConnection *>();
		// lazy load
	}
	return std::vector<IConnection*>(*_connections);
}

Person::~Person() {

}