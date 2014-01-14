#ifndef ADVANCEDMODE_FRIENDSHIPREQUESTNOTIFICATION_H
#define ADVANCEDMODE_FRIENDSHIPREQUESTNOTIFICATION_H

#include "../../Models/IFriendshipRequestNotification.h"

namespace AdvancedMode {
	class Cache;
	
	class FriendshipRequestNotification : public IFriendshipRequestNotification {
		public:
			FriendshipRequestNotification(int id, bool read, Cache * cache);

			virtual IPerson * getFrom();

			virtual IConnection * getConnection();

			virtual bool accept();
			virtual bool challenge(IMinigame * minigame, int level);
			virtual bool refuse();
			
			virtual long int getDate();
			
			virtual bool isRead();
			virtual void setRead(bool read);

			virtual ~FriendshipRequestNotification();

		private:
			Cache * cache;
			
			int id;
			bool read;
			int connectionId;
			IConnection * connectionToMe = NULL, * connectionFromMe = NULL;
			
			bool loaded; // lazy loading
			
			void load();
	};
}

#endif // ADVANCEDMODE_FRIENDSHIPREQUESTNOTIFICATION_H
