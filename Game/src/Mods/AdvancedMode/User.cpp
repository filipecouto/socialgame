#include "User.h"
#include "Person.h"
#include "Cache.h"
#include "ConnectionsList.h"

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
	((ConnectionsList *) getPerson()->getConnections())->loadList();
	((ConnectionsList *) friendToAdd->getConnections())->loadList();

	cache->getService()->addFriend(((Person *)friendToAdd)->getId());
}

void AdvancedMode::User::removeFriend(IPerson * friendToRemove) {
	((ConnectionsList *) getPerson()->getConnections())->removeConnection(friendToRemove);
	((ConnectionsList *) friendToRemove->getConnections())->removeConnection(getPerson());

	cache->getService()->removeFriend(((Person *)friendToRemove)->getId());
}

AdvancedMode::User::~User() {

}
