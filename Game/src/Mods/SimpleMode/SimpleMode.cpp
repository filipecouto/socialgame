/**
 * TestMod - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "SimpleMode.h"

SimpleMode::SimpleMode() {

}

SimpleMode::~SimpleMode() {

}

void SimpleMode::load() {

}

IUser * SimpleMode::getIdentity() {
	return &user;
}

void * SimpleMode::getNotifications() {
	return NULL;
}

void * SimpleMode::getPendingGames() {
	return NULL;
}
