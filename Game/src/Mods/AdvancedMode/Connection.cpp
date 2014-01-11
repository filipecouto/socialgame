#include "Connection.h"
#include "Person.h"
#include "Cache.h"

AdvancedMode::Connection::Connection(int from, const rapidjson::Value & data, AdvancedMode::Cache * cache) : cache(cache) {
	id = std::stoi(data["id"].GetString());
	int user1 = std::stoi(data["user1"].GetString());
	int user2 = std::stoi(data["user2"].GetString());
	personId = user1 == from ? user2 : user1;
	
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
