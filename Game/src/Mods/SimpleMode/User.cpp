/*
 * User - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "User.h"
#include "Person.h"
#include "Mood.h"

using namespace SimpleMode;

User::User() {
	player = new Person("Phillip", new Mood("ANGRY"));
	Person * p1 = new Person("Terrence", new Mood("Maybe Maybe"));
	Person * p2 = new Person("William", new Mood("Maybe Fresh"));
	Person * p3 = new Person("Ferdinand", new Mood("Maybe I don't know"));
	Person * p4 = new Person("Gil", new Mood("Maybe Salty"));
	Person * p5 = new Person("Homer", new Mood("Maybe Salty"));
	Person * p6 = new Person("Socrates", new Mood("Maybe Salty"));
	Person * p7 = new Person("John", new Mood("..."));
	Person * p8 = new Person("Mary", new Mood("......"));
	Person * p9 = new Person("Lucinda", new Mood("uiop"));

	player->connect(p1);
	player->connect(p2);
	player->connect(p3);
	player->connect(p6);
	p3->connect(p2);
	p2->connect(p4);
	p4->connect(p5);
	p5->connect(p7);
	p7->connect(p8);
	p7->connect(p9);
}

IPerson * User::getPerson() {
	return player;
}

void User::addFriend(Person * friendToAdd) {

}

void User::addFriend(IPerson * friendToAdd) {

}

void User::removeFriend(IPerson * friendToRemove) {

}

void User::setMood(IMood * mood) {
	IUser::setMood(mood);
}

void User::setTags(std::vector< std::string > tags) {

}


User::~User(){

}

void User::setEventListener(GameModEventListener * listener) {
	
}

