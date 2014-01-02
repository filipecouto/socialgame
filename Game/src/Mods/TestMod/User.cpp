/*
 * User - Implementation
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#include "User.h"
#include "MessageNotification.h"
#include "FriendshipRequestNotification.h"

User::User() : ritinha("Bbb Ritinha Nogueirinha", Mood("Maybe Happy")) {
	Person * p1 = new Person("AAz Miquelina", Mood("Maybe Maybe"));
	Person * p2 = new Person("Azz Alface", Mood("Maybe Fresh"));
	Person * p3 = new Person("zzz Fernando", Mood("Maybe I don't know"));
	Person * p4 = new Person("zzA Alho Batata", Mood("Maybe Salty"));
	Person * p5 = new Person("zAA Batata Frita", Mood("Maybe Salty"));
	Person * p6 = new Person("zAz Batata Cozida", Mood("Maybe Salty"));
	Person * p7 = new Person("Alguem", Mood("..."));
	Person * p8 = new Person("Outro Alguem", Mood("......"));
	Person * p9 = new Person("qwerty", Mood("uiop"));

	ritinha.connect(p1);
	ritinha.connect(p2);
	ritinha.connect(p3);
	ritinha.connect(p6);
	p3->connect(p2);
	p2->connect(p4);
	p4->connect(p5);
	p5->connect(p7);
	p7->connect(p8);
	p7->connect(p9);
}

IPerson * User::getPerson() {
	return &ritinha;
}

void User::addFriend(IPerson * friendToAdd) {
	int accept = rand() % 4 - 1;
	if (accept > 1) accept = 1;
	ritinha.connect((Person *)friendToAdd, accept);
	if(accept == 0)
		_listener->onNewNotification(new MessageNotification("Friendship request sent."));
	else
		_listener->onNewNotification(new FriendshipRequestNotification(ritinha.getConnections()->operator[](ritinha.getConnections()->size() - 1)));
}

void User::setEventListener(GameModEventListener * listener) {
	_listener = listener;
}

User::~User() {

}
