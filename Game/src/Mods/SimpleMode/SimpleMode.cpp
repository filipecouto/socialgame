/**
 * TestMod - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "SimpleMode.h"
#include "Mood.h"
#include "User.h"
#include "MoodsList.h"
#include "MessageNotification.h"

SimpleMode::SimpleMode::SimpleMode() {

}

IMoodsList * SimpleMode::SimpleMode::getMoods() {
	return NULL;
}
IUser * SimpleMode::SimpleMode::getIdentity() {
	if (!user) {
		user = new User();
	}

	return user;
}

INotificationsList * SimpleMode::SimpleMode::getNotifications() {
	return NULL;
}

IPendingGamesList * SimpleMode::SimpleMode::getPendingGames() {
	return NULL;
}



SimpleMode::SimpleMode::~SimpleMode() {

}

void SimpleMode::SimpleMode::load() {
	_listener->onNewNotification(
	  new MessageNotification(
	    "Welcome to the normal mode of the Social Game!\nUnfortunately this mode is under development and not fully supported yet. It may crash."));
}



void SimpleMode::SimpleMode::setEventListener(GameModEventListener * listener) {
	_listener = listener;
	getIdentity();
	user->setEventListener(listener);
}
