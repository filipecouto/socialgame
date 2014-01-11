#include "FriendsList.h"

int FriendsList::getFriendsCount() {
	int result = 0;
	int len = size();

	for (int i = 0; i < len; i++) {
		IConnection * con = operator[](i);

		if (con->getState() == 1) result ++;
	}

	return result;
}

IConnection * FriendsList::getConnectionWith(IPerson * person) {
	int len = size();

	for (int i = 0; i < len; i++) {
		if (person == operator[](i)->getPerson()) return operator[](i);
	}
	
	return NULL;
}

bool FriendsList::isFriendsWith(IPerson * person) {
	int len = size();

	for (int i = 0; i < len; i++) {
		if (person == operator[](i)->getPerson() && operator[](i)->getState() == 1) return true;
	}
	
	return false;
}

bool FriendsList::hasFriend(IPerson * person) {
	int len = size();

	for (int i = 0; i < len; i++) {
		if (person == operator[](i)->getPerson()) return true;
	}
	
	return false;
}
