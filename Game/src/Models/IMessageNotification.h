/**
 * IMessageNotification - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef IMESSAGENOTIFICATION_H
#define IMESSAGENOTIFICATION_H

#include "INotification.h"
#include "IUser.h"

class IMessageNotification : public INotification {
	public:
		NotificationType getType() { return Message; };

		virtual IUser * getFrom() = 0;
		
		virtual std::string getMessage() = 0;

		virtual ~IMessageNotification() { }
};

#endif