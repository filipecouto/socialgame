#ifndef SM_MESSAGENOTIFICATION_H
#define SM_MESSAGENOTIFICATION_H

#include "../../Models/IMessageNotification.h"

namespace SimpleMode {
	class MessageNotification : public IMessageNotification {
		public:
			MessageNotification(std::string message);

			IPerson * getFrom();
			virtual std::string getMessage();

			virtual long int getDate();

			virtual bool isRead();
			virtual void setRead();

			~MessageNotification();

		private:
			std::string _message;
	};
}
#endif // SM_MESSAGENOTIFICATION_H
