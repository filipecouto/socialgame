#include "Mood.h"

using namespace AdvancedMode;

Mood::Mood(int id, std::string description) : id(id), description(description) {

}

int Mood::getId() {
	return id;
}

std::string Mood::getDescription() {
	return description;
}

Mood::~Mood() {

}
