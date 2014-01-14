/**
 * TestMod - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "TestMod.h"
#include "MessageNotification.h"
#include "FriendshipRequestNotification.h"
#include "Mood.h"

TestMod::TestMod() {

}

void TestMod::load() {

// 	_listener->onNewNotification(new MessageNotification(
// 	                               "Welcome to the Social Game, you are playing in a test mod.\n"\
// 	                               "This mod is only used for the development of the game.\n"\
// 	                               "In order to interact with the game, click a person (sphere) and add them as friends.\n"\
// 	                               "Try the camera button above in order to move around the world differently (not completely implemented yet).\n"
// 	                               "Being this a test mod, this message is also used to test the connection between the game and the GUI."));
}

void TestMod::doSomething() {
	Person * p10 = new Person("Pessoa que quer ser amiga", new Mood("Feliz se for amiga"));
	_listener->onNewNotification(new FriendshipRequestNotification(&user, ((Person *) user.getPerson())->connect(p10, 0)));
}

IUser * TestMod::getIdentity() {
	return &user;
}

INotificationsList * TestMod::getNotifications() {
	return NULL;
}

IPendingGamesList * TestMod::getPendingGames() {
	return NULL;
}

IMoodsList * TestMod::getMoods() {
	return NULL;
}

void TestMod::setEventListener(GameModEventListener * listener) {
	_listener = listener;
	user.setEventListener(listener);
}

TestMod::~TestMod() {

}
