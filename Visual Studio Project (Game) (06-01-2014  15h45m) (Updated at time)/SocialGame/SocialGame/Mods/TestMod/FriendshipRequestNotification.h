#ifndef FRIENDSHIPREQUESTNOTIFICATION_H
#define FRIENDSHIPREQUESTNOTIFICATION_H

#include "../../Models/IFriendshipRequestNotification.h"

class FriendshipRequestNotification : public IFriendshipRequestNotification {
	public:
		FriendshipRequestNotification(IConnection * connection);

		virtual IPerson * getFrom();
		virtual IConnection * getConnection();

		virtual long int getDate();

		virtual bool isRead();
		virtual void setRead();

		~FriendshipRequestNotification();

	private:
		IConnection * _connection;
};
#endif // FRIENDSHIPREQUESTNOTIFICATION_H
