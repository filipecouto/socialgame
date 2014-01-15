#include "Connection.h"
#include "Person.h"
#include "Cache.h"

AdvancedMode::Connection::Connection(const rapidjson::Value & data, AdvancedMode::Cache * cache) : cache(cache) {
	_from = -1;
	
	load(data);
}

AdvancedMode::Connection::Connection(int from, const rapidjson::Value & data, AdvancedMode::Cache * cache) : cache(cache) {
	_from = from;
	
	load(data);
}

void AdvancedMode::Connection::reload() {
	const rapidjson::Value & data = cache->getService()->getConnection(id)[rapidjson::SizeType(0)];
	load(data);
}

void AdvancedMode::Connection::load(const rapidjson::Value & data) {
	id = std::stoi(data["id"].GetString());
	int user1 = std::stoi(data["user1"].GetString());
	int user2 = std::stoi(data["user2"].GetString());
	personId = user1 == _from ? user2 : user1;
	person = NULL;

	state = std::stoi(data["state"].GetString());
	strength = std::stoi(data["strength"].GetString());
	score = std::stoi(data["totalScore"].GetString());
}

IPerson * AdvancedMode::Connection::getPerson() {
	if (!person) {
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

void AdvancedMode::Connection::setState(int state) {
	this->state = state;
}

ITagsList * AdvancedMode::Connection::getTags() {
	return NULL;
}
