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

std::string Person::getName() {
	return _test == 0 ? "Ritinha" : _test == 1 ? "Alho Batata" : "Batata Frita";
}

Mood Person::getMood() {
	return Mood("meibi epi");
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

std::vector< IConnection * > Person::getConnections() {
	if (_connections == NULL) {
		_connections = new std::vector<IConnection *>();

		if (_test < 2) {
			Person * p = new Person();
			p->test(_test == 0 ? 1 : 2);
			_connections->push_back(new Connection(p));
			_connections->push_back(new Connection());

			if (_test == 0) {
				_connections->push_back(new Connection());
				_connections->push_back(new Connection());
			}
		}
	}

	return std::vector<IConnection *>(*_connections);
}

Person::~Person() {

}
