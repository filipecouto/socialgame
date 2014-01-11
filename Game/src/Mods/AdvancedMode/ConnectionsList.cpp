#include "ConnectionsList.h"
#include "CentralServerWebService.h"
#include "Person.h"
#include "Connection.h"
#include "Cache.h"

using namespace AdvancedMode;

ConnectionsList::ConnectionsList(Person * from, Cache * cache) : from(from), cache(cache) {
	loadList();
}

void ConnectionsList::loadList() {
	connections.clear();
	
	const rapidjson::Value & list = cache->getService()->getConnectionsOfUser(from->getId());

	rapidjson::SizeType len = list.Size();

	for (rapidjson::SizeType i = 0; i < len; i++) {
		connections.push_back(new Connection(from->getId(), list[i], cache));
	}
}

int ConnectionsList::getFriendsCount() {
	int result = 0;
	int len = size();

	for (int i = 0; i < len; i++) {
		if (connections[i]->getState() == 1) result++;
	}

	return result;
}

bool ConnectionsList::isFriendsWith(IPerson * person) {
	IConnection * connection = getConnectionWith(person);

	return connection && connection->getState() == 1;
}

IConnection * ConnectionsList::getConnectionWith(IPerson * person) {
	int len = size();

	for (int i = 0; i < len; i++) {
		if (person == connections[i]->getPerson()) return connections[i];
	}

	loadList();
	len = size();

	for (int i = 0; i < len; i++) {
		if (person == connections[i]->getPerson()) return connections[i];
	}

	return NULL;
}

void ConnectionsList::removeConnection(IPerson * person) {
	int len = size();
	
	for(int i = 0; i < len; i++) {
		if(connections[i]->getPerson() == person) {
			connections.erase(connections.begin() + i);
			return;
		}
	}
}

int ConnectionsList::size() {
	return connections.size();
}

IConnection * ConnectionsList::operator[](int index) {
	return connections[index];
}

bool ConnectionsList::contains(IConnection * item) {
	int len = size();

	for (int i = 0; i < len; i++) {
		if (item == connections[i]) return true;
	}

	return false;
}
