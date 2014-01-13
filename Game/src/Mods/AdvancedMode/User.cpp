#include "User.h"
#include "Person.h"
#include "Cache.h"
#include "ConnectionsList.h"
#include "Mood.h"

AdvancedMode::User::User(Cache * cache) : cache(cache) {
	id = cache->getService()->getUserId();
}

IPerson * AdvancedMode::User::getPerson() {
	if (!person) {
		person = cache->getPerson(id);
		cache->setIdentityPerson(person);
	}

	return person;
}

void AdvancedMode::User::addFriend(IPerson * friendToAdd) {
	if (cache->getService()->addFriend(((Person *)friendToAdd)->getId())) {
		((ConnectionsList *) getPerson()->getConnections())->loadList();
		((ConnectionsList *) friendToAdd->getConnections())->loadList();
	}
}

void AdvancedMode::User::removeFriend(IPerson * friendToRemove) {
	if (cache->getService()->removeFriend(((Person *)friendToRemove)->getId())) {
		((ConnectionsList *) getPerson()->getConnections())->removeConnection(friendToRemove);
		((ConnectionsList *) friendToRemove->getConnections())->removeConnection(getPerson());
	}
}

void AdvancedMode::User::setMood(IMood * mood) {
	if (cache->getService()->setMood((((Mood *)mood)->getId()))) {
		((Person *)getPerson())->setMood(mood);
	}
}

void AdvancedMode::User::setTags(vector< string > tags) {
	
}

AdvancedMode::User::~User() {

}
