/**
 * FriendshipRequestNotification - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef IFRIENDSHIPREQUESTNOTIFICATION_H
#define IFRIENDSHIPREQUESTNOTIFICATION_H

#include "INotification.h"
#include "IPerson.h"
#include "IConnection.h"

class IFriendshipRequestNotification : public INotification {
	public:
		NotificationType getType() { return FriendshipRequest; };

		virtual IPerson * getFrom() = 0;
		
		virtual IConnection * getConnection() = 0;

		virtual ~IFriendshipRequestNotification() { }
};

#endif
