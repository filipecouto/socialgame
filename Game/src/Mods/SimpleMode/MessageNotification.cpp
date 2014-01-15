#include "MessageNotification.h"

using namespace SimpleMode;

MessageNotification::MessageNotification(std::string message) {
	_message = message;
}

std::string MessageNotification::getMessage() {
	return _message;
}

IPerson * MessageNotification::getFrom() {
	return NULL;
}

long int MessageNotification::getDate() {
	return -1;
}

bool MessageNotification::isRead() {
	return false;
}

void MessageNotification::setRead() {

}

MessageNotification::~MessageNotification() {

}
