#include "User.h"
#include "Person.h"
#include "Cache.h"

AdvancedMode::User::User(Cache * cache) : cache(cache) {
	id = cache->getService()->getUserId();
}

IPerson * AdvancedMode::User::getPerson() {
	if(!person) {
		person = cache->getPerson(id);
	}
	
	return person;
}

void AdvancedMode::User::addFriend(IPerson * friendToAdd) {

}

AdvancedMode::User::~User() {

}
