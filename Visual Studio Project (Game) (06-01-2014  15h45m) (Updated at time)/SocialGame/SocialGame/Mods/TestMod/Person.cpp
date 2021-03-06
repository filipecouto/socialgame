/*
 * Person - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 *
 */

#include "Person.h"
#include "Connection.h"

Person::Person(std::string name, Mood mood) {
	_name = name;
	_mood = mood;
	
	_connections = new FriendsList();
}

std::string Person::getName() {
	return _name;
}

Mood Person::getMood() {
	return _mood;
}

int Person::getScore() {
	return 1000;
}

int Person::getStrength() {
	return 8;
}

std::vector<Tag *> Person::getTags() {
	return std::vector<Tag *>();
}

void Person::connect(Person * other) {
	_connections->add(new Connection(other));
	other->_connections->add(new Connection(this));
}

void Person::connect(Person * other, int state) {
	_connections->add(new Connection(other, state));
	other->_connections->add(new Connection(this, state));
}

IConnectionsList * Person::getConnections() {
// 	if (_connections == NULL) {
// 		_connections = new std::vector<IConnection *>();
// 
// 		if (_test < 2) {
// 			Person * p = new Person();
// 			p->test(_test == 0 ? 1 : 2);
// 			_connections->push_back(new Connection(p));
// 			_connections->push_back(new Connection());
// 			_connections->push_back(new Connection());
// 			_connections->push_back(new Connection());
// 
// 			if (_test == 0) {
// 				_connections->push_back(new Connection());
// 				_connections->push_back(new Connection());
// 			} else {
// 				_connections->push_back(new Connection(this));
// 			}
// 		}
// 	}

	return _connections;
}

Person::~Person() {

}
