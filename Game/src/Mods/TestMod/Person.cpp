/*
 * Person - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 *
 */

#include "Person.h"

std::string Person::getName() {
	return "Ritinha";
}

Mood Person::getMood() {
	return Mood("meibi epi");
}

int Person::getScore() {
	return 1000;
}

int Person::getStrength() {
	return 8;
}
