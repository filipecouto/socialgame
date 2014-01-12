#include "Person.h"
#include "ConnectionsList.h"
#include "Cache.h"

AdvancedMode::Person::Person(int id, Cache * cache) : Person(cache->getService()->getPerson(id), cache) {
}

AdvancedMode::Person::Person(const rapidjson::Value & data, Cache * cache) : cache(cache) {
	id = std::stoi(data["id"].GetString());
	name = data["username"].GetString();

	if (data["moodId"].IsString()) {
		mood = cache->getMoods()->getMoodByID(std::stoi(data["moodId"].GetString()));
	}
}

int AdvancedMode::Person::getId() {
	return id;
}

std::string AdvancedMode::Person::getName() {
	return name;
}

IConnectionsList * AdvancedMode::Person::getConnections() {
	if (!connections) {
		connections = new ConnectionsList(this, cache);
	}

	return connections;
}

ITagsList * AdvancedMode::Person::getTags() {
	return NULL;
}

int AdvancedMode::Person::getStrength() {
	return 0;
}

int AdvancedMode::Person::getScore() {
	return 0;
}

IMood * AdvancedMode::Person::getMood() {
	return mood;
}

AdvancedMode::Person::~Person() {

}