#include "Mood.h"

using namespace SimpleMode;

Mood::Mood(std::string description) : description(description) {

}

Mood::~Mood() {

}

std::string Mood::getDescription() {
	return description;
}