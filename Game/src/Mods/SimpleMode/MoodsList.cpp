#include "MoodsList.h"

using namespace SimpleMode;

MoodsList::MoodsList() {

}

MoodsList::~MoodsList() {

}

bool MoodsList::contains(IMood * item) {
	for(int i = 0; i < moods.size(); i++) {
		IMood * something = moods.at(i);
		if(something->getDescription() == item->getDescription()) {
			return true;
		}
	}
	return false;
}

IMood * MoodsList::operator[](int index) {
	return moods[index];
}

int MoodsList::size() {
	return moods.size();
}

void MoodsList::addMood(IMood * mood) {
	moods.push_back(mood);
}
