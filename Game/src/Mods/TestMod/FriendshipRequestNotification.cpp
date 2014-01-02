#include "FriendshipRequestNotification.h"

FriendshipRequestNotification::FriendshipRequestNotification(IConnection * connection) {
	_connection = connection;
}

IConnection * FriendshipRequestNotification::getConnection() {
	return _connection;
}

IPerson * FriendshipRequestNotification::getFrom() {
	return NULL;
}

long int FriendshipRequestNotification::getDate() {
	return -1;
}

bool FriendshipRequestNotification::isRead() {
	return false;
}

void FriendshipRequestNotification::setRead() {

}

FriendshipRequestNotification::~FriendshipRequestNotification() {

}
