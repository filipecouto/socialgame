/**
 * INotificationsList - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef INOTIFICATIONSLIST_H
#define INOTIFICATIONSLIST_H

#include "IList.h"
#include "INotification.h"

class INotificationsList : public IList<INotification*> {
	public:
		virtual int getUnreadCount() = 0;
		
		virtual ~INotificationsList() { }
};

#endif
