#ifndef MESSAGENOTIFICATION_H
#define MESSAGENOTIFICATION_H

#include "../../Models/IMessageNotification.h"

class MessageNotification : public IMessageNotification {
	public:
		MessageNotification(std::string message);

		virtual IUser * getFrom();
		virtual std::string getMessage();

		virtual long int getDate();

		virtual bool isRead();
		virtual void setRead();

		~MessageNotification();

	private:
		std::string _message;
};
#endif // MESSAGENOTIFICATION_H
