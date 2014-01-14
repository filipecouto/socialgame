#include "Language.h"

Language::Language(std::string name, std::string path) {
	_name = name;
	_path = path;
}

Language::~Language() {

}

std::string Language::getName() {
	return _name;
}

std::string Language::getPath() {
	return _path;
}