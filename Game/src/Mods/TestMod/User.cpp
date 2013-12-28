/*
 * User - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "User.h"

User::User() : ritinha("AAA Ritinha Nogueirinha", Mood("Maybe Happy")) {
	Person * p1 = new Person("AAz Miquelina", Mood("Maybe Maybe"));
	Person * p2 = new Person("Azz Alface", Mood("Maybe Fresh"));
	Person * p3 = new Person("zzz Fernando", Mood("Maybe I don't know"));
	Person * p4 = new Person("zzA Alho Batata", Mood("Maybe Salty"));
	Person * p5 = new Person("zAA Batata Frita", Mood("Maybe Salty"));
	Person * p6 = new Person("zAA Batata Cozida", Mood("Maybe Salty"));
	
	ritinha.connect(p1);
	ritinha.connect(p2);
	ritinha.connect(p3);
	ritinha.connect(p6);
	p3->connect(p2);
	p2->connect(p4);
	p4->connect(p5);
}

IPerson * User::getPerson() {
	return &ritinha;
}

void User::addFriend(IPerson * friendToAdd) {

}

User::~User(){

}
