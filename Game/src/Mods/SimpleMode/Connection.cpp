#include "Connection.h"
#include "Person.h"

using namespace SimpleMode;

Connection::Connection(Person * person) : person(person) {

}

IPerson * Connection::getPerson() {
	return person;
}

int Connection::getScore() {
	return 0;
}

int Connection::getState() {
	return 0;
}

int Connection::getStrength() {
	return 0;
}

void Connection::load() {

}

void Connection::reload() {

}
ITagsList * Connection::getTags() {
	return NULL;
}


void Connection::setState(int state) {

}

Connection::~Connection() {

}

