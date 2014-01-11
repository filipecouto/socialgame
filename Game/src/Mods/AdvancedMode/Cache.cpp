#include "Cache.h"
#include "Person.h"

AdvancedMode::Cache::Cache(CentralServerWebService * service, MoodsList * moods) : service(service), moods(moods) {

}

CentralServerWebService * AdvancedMode::Cache::getService() {
	return service;
}

AdvancedMode::MoodsList * AdvancedMode::Cache::getMoods() {
	return moods;
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

AdvancedMode::Cache::~Cache() {

}
