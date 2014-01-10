#include "ConnectionsList.h"
#include "CentralServerWebService.h"
#include "Person.h"
#include "Connection.h"
#include "Cache.h"

using namespace AdvancedMode;

ConnectionsList::ConnectionsList(Person * from, Cache * cache) : cache(cache) {
	const rapidjson::Value & list = cache->getService()->getConnectionsOfUser(from->getId());

	rapidjson::SizeType len = list.Size();

	for (rapidjson::SizeType i = 0; i < len; i++) {
		connections.push_back(new Connection(list[i], cache));
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
	int len = size();

	for (int i = 0; i < len; i++) {
		if (person == connections[i]->getPerson() && connections[i]->getState() == 1) return true;
	}

	return false;
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
