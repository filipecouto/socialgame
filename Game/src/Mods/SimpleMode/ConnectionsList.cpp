#include "ConnectionsList.h"

using namespace SimpleMode;

ConnectionsList::ConnectionsList() {

}

ConnectionsList::~ConnectionsList() {

}

bool ConnectionsList::contains(IConnection * item) {
	return true;
}


int ConnectionsList::getFriendsCount() {
	int result = 0;
	int len = size();

	for (int i = 0; i < len; i++) {
		IConnection * con = operator[](i);

		if (con->getState() == 1) result ++;
	}

	return result;
}

bool ConnectionsList::isFriendsWith(IPerson * person) {
	for(int i = 0; i < size(); i++) {
		IConnection * connection = connections[i];
		return connection->getPerson()->getName() == person->getName();
	}
	return false;
}

IConnection * ConnectionsList::getConnectionWith(IPerson * person) {
	return NULL;
}

IConnection * ConnectionsList::operator[](int index) {
	return connections[index];
}

int ConnectionsList::size() {
	return connections.size();
}

void ConnectionsList::addConnection(IConnection* connection) {
	connections.push_back(connection);
}
