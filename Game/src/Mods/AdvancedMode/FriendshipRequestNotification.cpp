#include "FriendshipRequestNotification.h"
#include "Cache.h"
#include "Connection.h"
#include "ConnectionsList.h"
#include "../../Models/IConnectionsList.h"
#include "../../Minigames/IMinigame.h"

using namespace AdvancedMode;

FriendshipRequestNotification::FriendshipRequestNotification(int id, bool read, Cache * cache) : id(id), read(read), loaded(false), cache(cache) {

}

bool FriendshipRequestNotification::refuse() {
	if (!getConnection()) return false;

	if (cache->getService()->refuseFriendship(connectionId)) {
		((Connection *)connectionFromMe)->setState(-1);
		((Connection *)connectionToMe)->setState(-1);
		return true;
	} else {
		return false;
	}
}

bool FriendshipRequestNotification::challenge(IMinigame * minigame, int level) {
	if (!getConnection()) return false;

	if (cache->getService()->acceptFriendshipWithChallenge(connectionId, minigame->getInternalName(), level)) {
		return true;
	} else {
		return false;
	}
}

bool FriendshipRequestNotification::accept() {
	if (!getConnection()) return false;

	if (cache->getService()->acceptFriendship(connectionId)) {
		((Connection *)connectionFromMe)->setState(1);
		((Connection *)connectionToMe)->setState(1);
		return true;
	} else {
		return false;
	}
}

IConnection * FriendshipRequestNotification::getConnection() {
	if (!loaded) load();

	return connectionFromMe;
}

IPerson * FriendshipRequestNotification::getFrom() {
	return getConnection() ? getConnection()->getPerson() : NULL;
}

long int FriendshipRequestNotification::getDate() {
	return 0;
}

bool FriendshipRequestNotification::isRead() {
	return read;
}

void FriendshipRequestNotification::setRead(bool read) {
	cache->getService()->setNotificationRead(id, read);
	this->read = read;
}

void FriendshipRequestNotification::load() {
	const rapidjson::Value & data = cache->getService()->getNotification(id);
	connectionId = std::stoi(data["object"].GetString());
	const rapidjson::Value & connectionData = cache->getService()->getConnection(connectionId);

	if (!connectionData.IsFalse()) {
		IConnection * connection = new Connection(connectionData[(rapidjson::SizeType)0], cache);

		connectionToMe = ((ConnectionsList *)connection->getPerson()->getConnections())->getConnectionWith(cache->getIdentityPerson());
		connectionFromMe = ((ConnectionsList *)cache->getIdentityPerson()->getConnections())->getConnectionWith(connection->getPerson());
	}

	loaded = true;
}

FriendshipRequestNotification::~FriendshipRequestNotification() {

}
