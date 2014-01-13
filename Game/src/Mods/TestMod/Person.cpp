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

Person::Person(std::string name, IMood * mood) {
	_name = name;
	_mood = mood;
	
	_connections = new FriendsList();
}

std::string Person::getName() {
	return _name;
}

IMood * Person::getMood() {
	return NULL;
}

int Person::getScore() {
	return 1000;
}

int Person::getStrength() {
	return 8;
}

ITagsList * Person::getTags() {
	return NULL;
}

void Person::connect(Person * other) {
	_connections->add(new Connection(other));
	other->_connections->add(new Connection(this));
}

IConnection * Person::connect(Person * other, int state) {
	Connection * connection = NULL;

	if (_connections->hasFriend(other)) {
		int len = _connections->size();

		for (int i = 0; i < len; i++) {
			if (_connections->operator[](i)->getPerson() == other) {
				connection = (Connection *)_connections->operator[](i);
				connection->setState(state);
				break;
			}
		}

		len = other->_connections->size();

		for (int i = 0; i < len; i++) {
			if (other->_connections->operator[](i)->getPerson() == this) {
				((Connection *) other->_connections->operator[](i))->setState(state);
				break;
			}
		}
	} else {
		connection = new Connection(other, state);
		_connections->add(connection);
		other->_connections->add(new Connection(this, state));
	}

	return connection;
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
