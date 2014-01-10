/**
 * AdvancedMode - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "AdvancedMode.h"
#include "User.h"
#include "MoodsList.h"
#include "Cache.h"

AdvancedMode::AdvancedMode::AdvancedMode() {

}

void AdvancedMode::AdvancedMode::load() {
	moods = new MoodsList(service.getMoods(), &service);

	if (cache) delete cache;

	cache = new Cache(&service, moods);
}

int AdvancedMode::AdvancedMode::login(string email, string password) {
	int result = service.login(email, password);

	return result;
}

void * AdvancedMode::AdvancedMode::getPendingGames() {
	return NULL;
}

std::vector< INotification * > * AdvancedMode::AdvancedMode::getNotifications() {
	return new std::vector<INotification *>();
}

IUser * AdvancedMode::AdvancedMode::getIdentity() {
	if (!user) {
		user = new User(cache);
	}

	return user;
}

IMoodsList * AdvancedMode::AdvancedMode::getMoods() {
	return moods;
}

void AdvancedMode::AdvancedMode::setEventListener(GameModEventListener * listener) {

}

AdvancedMode::AdvancedMode::~AdvancedMode() {

}
