#include "FriendshipRequestNotification.h"
#include "Cache.h"
#include "Connection.h"

using namespace AdvancedMode;

FriendshipRequestNotification::FriendshipRequestNotification(int id, bool read, Cache * cache) : id(id), read(read), loaded(false), cache(cache) {

}

bool FriendshipRequestNotification::refuse() {
	return true;
}

bool FriendshipRequestNotification::accept() {
	return true;
}

IConnection * FriendshipRequestNotification::getConnection() {
	if(!loaded) load();
	return connection;
}

IPerson * FriendshipRequestNotification::getFrom() {
	return getConnection()->getPerson();
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
	connection = new Connection(cache->getService()->getConnection(std::stoi(data["object"].GetString())), cache);
	
	loaded = true;
}

FriendshipRequestNotification::~FriendshipRequestNotification() {

}
