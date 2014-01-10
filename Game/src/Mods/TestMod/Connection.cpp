/*
 * Connection - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "Connection.h"

// Connection::Connection() {
// 
// }

Connection::Connection(Person * p) : _state(1) {
	_p = p;
}

Connection::Connection(Person * p, int state) : _state(state) {
	_p = p;
}

ITagsList * Connection::getTags() {
	return NULL;
}

int Connection::getScore() {
	return 0;
}

int Connection::getStrength() {
	return 0;
}

int Connection::getState() {
	return _state;
}

void Connection::setState(int state) {
	_state = state;
}

IPerson * Connection::getPerson() {
	return (IPerson *) _p;
}

Connection::~Connection() {

}
