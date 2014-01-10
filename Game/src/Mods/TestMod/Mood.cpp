#include "Mood.h"

Mood::Mood(std::string name) {
	mood = name;
}

std::string Mood::getDescription() {
	return mood;
}

Mood::~Mood() {

}
