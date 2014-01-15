#include "Person.h"
#include "Mood.h"
#include "ConnectionsList.h"

using namespace SimpleMode;

Person::Person(std::string name, IMood * mood) : name(name), mood(mood){
	
}
ITagsList * Person::getTags() {
	return NULL;
}

Person::~Person() {

}

/*
 * Person - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 *
 */

#include "Person.h"
#include "ConnectionsList.h"
#include "Connection.h"
#include "../../Models/IConnectionsList.h"

std::string Person::getName() {
	return name;
}

IMood * Person::getMood() {
	return new Mood("Neutral");
}

int Person::getScore() {
	return 0;
}

int Person::getStrength() {
	return 0;
}

IConnectionsList * Person::getConnections() {
	if(_connections == NULL) {
		_connections = new ConnectionsList();
	}
	return _connections;
}

void Person::connect(Person * other) {
	if(_connections == NULL) {
		_connections = new ConnectionsList();
	}
	_connections->addConnection(new Connection(other));
	ConnectionsList * otherlist= (ConnectionsList*) other->getConnections();
	otherlist->addConnection(new Connection(this));
}