#ifndef ADVANCEDMODE_NOTIFICATIONSLIST_H
#define ADVANCEDMODE_NOTIFICATIONSLIST_H

#include "../../Models/INotificationsList.h"
#include <vector>

class IPerson;

namespace AdvancedMode {
	class Cache;
	
	class NotificationsList : public INotificationsList {
		public:
			NotificationsList(Cache * cache);

			virtual bool contains(INotification * item);
			virtual INotification * operator[](int index);
			
			virtual int size();
			virtual int getUnreadCount();

			~NotificationsList();

		private:
			Cache * cache;

			std::vector<INotification *> notifications;
	};
}

#endif // ADVANCEDMODE_NOTIFICATIONSLIST_H
