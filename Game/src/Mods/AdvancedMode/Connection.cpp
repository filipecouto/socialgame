#include "Connection.h"
#include "Person.h"
#include "Cache.h"

AdvancedMode::Connection::Connection(const rapidjson::Value & data, Cache * cache) : cache(cache) {
	id = std::stoi(data["id"].GetString());
	personId = std::stoi(data["user2"].GetString());
	
	state = std::stoi(data["state"].GetString());
	strength = std::stoi(data["strength"].GetString());
	score = std::stoi(data["totalScore"].GetString());
}

IPerson * AdvancedMode::Connection::getPerson() {
	if(!person) {
		person = cache->getPerson(personId);
	}
	
	return person;
}

int AdvancedMode::Connection::getScore() {
	return score;
}

int AdvancedMode::Connection::getStrength() {
	return strength;
}

int AdvancedMode::Connection::getState() {
	return state;
}
