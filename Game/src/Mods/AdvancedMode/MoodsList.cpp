#include "MoodsList.h"
#include "Mood.h"

AdvancedMode::MoodsList::MoodsList(const rapidjson::Value & data, CentralServerWebService * service) {
	rapidjson::SizeType len = data.Size();

	for (rapidjson::SizeType i = 0; i < len; i++) {
		const rapidjson::Value & mood = data[i];
		moods.push_back(new Mood(std::stoi(mood["id"].GetString()), mood["description"].GetString()));
	}
}

IMood * AdvancedMode::MoodsList::getMoodByID(int id) {
	int len = moods.size();

	for (int i = 0; i < len; i++) {
		if (((Mood *)moods[i])->getId() == id) return moods[i];
	}

	return NULL;
}

bool AdvancedMode::MoodsList::contains(IMood * item) {
	int len = moods.size();

	for (int i = 0; i < len; i++) {
		if (item == moods[i]) return true;
	}

	return false;
}

IMood * AdvancedMode::MoodsList::operator[](int index) {
	return moods[index];
}

int AdvancedMode::MoodsList::size() {
	return moods.size();
}

AdvancedMode::MoodsList::~MoodsList() {
	int len = moods.size();

	for (int i = 0; i < len; i++) {
		delete moods[i];
	}
}
