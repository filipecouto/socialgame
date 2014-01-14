#include "FriendshipRequestNotification.h"

FriendshipRequestNotification::FriendshipRequestNotification(IConnection * connection) : _connection(connection) {
}

FriendshipRequestNotification::FriendshipRequestNotification(User * user, IConnection * connection) : _user(user), _connection(connection) {

}

IConnection * FriendshipRequestNotification::getConnection() {
	return _connection;
}

bool FriendshipRequestNotification::accept() {
	((Person*)_user->getPerson())->connect((Person*)_connection->getPerson(), 1);
	return true;
}

bool FriendshipRequestNotification::challenge(IMinigame * minigame, int level) {
	return true;
}

bool FriendshipRequestNotification::refuse() {
	((Person*)_user->getPerson())->connect((Person*)_connection->getPerson(), -1);
	return true;
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
