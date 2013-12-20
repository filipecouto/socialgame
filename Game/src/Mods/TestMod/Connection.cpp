/*
 * Connection - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "Connection.h"

Connection::Connection() {

}

Connection::Connection(Person * p) {
	_p = p;
}

std::vector< Tag * > Connection::getTags() {
	return std::vector<Tag *>();
}

int Connection::getScore() {
	return 0;
}

int Connection::getStrength() {
	return 0;
}

int Connection::getState() {
	return 0;
}

IPerson * Connection::getPerson() {
	return _p;
}

Connection::~Connection() {

}
