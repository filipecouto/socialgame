/**
 * INotification - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef INOTIFICATION_H
#define INOTIFICATION_H

class INotification {
	public:
		enum NotificationType { Unknown, Message, FriendshipRequest };
		
		virtual NotificationType getType() { return Unknown; }
		
		virtual bool isRead() = 0;
		virtual void setRead(bool read) { }
		
		/**
		 * Gets the date and time this notification was sent in Unix-like format
		 */
		virtual long getDate() = 0;

		virtual ~INotification() { }
};

#endif
