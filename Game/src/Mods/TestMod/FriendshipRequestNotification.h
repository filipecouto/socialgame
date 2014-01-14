#ifndef FRIENDSHIPREQUESTNOTIFICATION_H
#define FRIENDSHIPREQUESTNOTIFICATION_H

#include "../../Models/IFriendshipRequestNotification.h"
#include "User.h"

class FriendshipRequestNotification : public IFriendshipRequestNotification {
	public:
		FriendshipRequestNotification(IConnection * connection);
		FriendshipRequestNotification(User * user, IConnection * connection);

		virtual IPerson * getFrom();
		virtual IConnection * getConnection();

		virtual long int getDate();

		virtual bool isRead();
		virtual void setRead();
		
		virtual bool accept();
		virtual bool challenge(IMinigame * minigame, int level);
		virtual bool refuse();

		~FriendshipRequestNotification();

	private:
		User * _user = NULL;
		IConnection * _connection;
};
#endif // FRIENDSHIPREQUESTNOTIFICATION_H
