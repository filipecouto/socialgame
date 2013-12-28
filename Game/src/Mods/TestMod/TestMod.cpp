/**
 * TestMod - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "TestMod.h"
#include "MessageNotification.h"

TestMod::TestMod() {

}

void TestMod::load() {
	_listener->onNewNotification(new MessageNotification("Welcome to the Social Game, you are playing in a test mod."));
}

IUser * TestMod::getIdentity() {
	return &user;
}

std::vector<INotification *> * TestMod::getNotifications() {
	return NULL;
}

void * TestMod::getPendingGames() {
	return NULL;
}

void TestMod::setEventListener(GameModEventListener * listener) {
	_listener = listener;
}

TestMod::~TestMod() {

}
