#include "NotificationsList.h"
#include "Cache.h"
#include "FriendshipRequestNotification.h"

AdvancedMode::NotificationsList::NotificationsList(Cache * cache) : cache(cache) {
	const rapidjson::Value & list = cache->getService()->getNotificationBases();

	if (list.IsArray()) {
		rapidjson::SizeType len = list.Size();

		for (rapidjson::SizeType i = 0; i < len; i++) {
			const rapidjson::Value & item = list[i];

			if (item["type"].GetString()[0] == '1') {
				notifications.push_back(new FriendshipRequestNotification(std::stoi(item["id"].GetString()), item["read"].GetString()[0] == '1', cache));
			}
		}
	}
}

bool AdvancedMode::NotificationsList::contains(INotification * item) {
	int len = size();

	for (int i = 0; i < len; i++) {
		if (item == notifications[i]) return true;
	}

	return false;
}

int AdvancedMode::NotificationsList::getUnreadCount() {
	int len = size();
	int count = 0;

	for (int i = 0; i < len; i++) {
		if (!notifications[i]->isRead()) count++;
	}

	return count;
}

INotification * AdvancedMode::NotificationsList::operator[](int index) {
	return notifications[index];
}

int AdvancedMode::NotificationsList::size() {
	return notifications.size();
}

AdvancedMode::NotificationsList::~NotificationsList() {

}
