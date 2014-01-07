/*
 * User - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "User.h"

IPerson * User::getPerson() {
	return &player;
}

void User::addFriend(IPerson * friendToAdd) {

}

User::~User(){

}
