#include "Cache.h"
#include "Person.h"
#include "Connection.h"
#include "Tag.h"

AdvancedMode::Cache::Cache(CentralServerWebService * service, MoodsList * moods) : service(service), moods(moods) {

}

CentralServerWebService * AdvancedMode::Cache::getService() {
	return service;
}

AdvancedMode::MoodsList * AdvancedMode::Cache::getMoods() {
	return moods;
}

IPerson * AdvancedMode::Cache::getIdentityPerson() {
	return identityPerson;
}

void AdvancedMode::Cache::setIdentityPerson(IPerson * person) {
	identityPerson = person;
}

IPerson * AdvancedMode::Cache::getPerson(int id) {
	const int len = people.size();

	for (int i = 0; i < len; i++) {
		if (people[i]->getId() == id) return people[i];
	}

	Person * newPerson = new Person(id, this);
	people.push_back(newPerson);

	return newPerson;
}

ITag * AdvancedMode::Cache::getUserTag(int id) {
	const int len = userTags.size();
	
	for(int i = 0; i < len; i++) {
		if(userTags[i]->getId() == id) return userTags[i];
	}
	
	Tag * newTag = new Tag(id, this);
	userTags.push_back(newTag);
	
	return newTag;
}

AdvancedMode::Cache::~Cache() {

}
