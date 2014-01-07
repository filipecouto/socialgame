/**
 * AdvancedMode - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "AdvancedMode.h"

AdvancedMode::AdvancedMode() {

}

void AdvancedMode::load() {

}

void * AdvancedMode::getPendingGames() {
	return NULL;
}

std::vector< INotification * > * AdvancedMode::getNotifications() {
	return new std::vector<INotification*>();
}

IUser * AdvancedMode::getIdentity() {
	return NULL;
}

AdvancedMode::~AdvancedMode() {

}
