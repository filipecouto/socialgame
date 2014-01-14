#include "LanguageLoader.h"
#include <string.h>

LanguageLoader::LanguageLoader() {

}

LanguageLoader::~LanguageLoader() {

}

std::vector< Language > LanguageLoader::getLanguages() {
	if (_languages.size() == 0) {
		_languages = loadLanguages();
	}

	return _languages;

}

std::vector< Language > LanguageLoader::loadLanguages() {
	std::string s1, s2, line;
	std::ifstream infile;
	int pos = 0;
	infile.open("languages");
	std::vector<Language> languages;

	while (!infile.eof()) {
		getline(infile, line);
		pos = line.find_first_of("=");
		s1 = line.substr(0, pos - 1);
		s2 = line.substr(pos + 1, line.size());
		Language * language = new Language(s1, s2);
		languages.push_back(*language);
	}

	infile.close();
	return languages;
}

void LanguageLoader::setLanguage(Language language) {
	std::string s1, s2, line;
	std::ifstream infile;
	int pos = 0;
	infile.open(language.getPath());
	_loaded.clear();

	while (!infile.eof()) {
		getline(infile, line);
		pos = line.find_first_of("=");
		s1 = line.substr(0, pos - 1);
		s2 = line.substr(pos + 1, line.size());
		_loaded.insert(std::pair<std::string, std::string>(s1, s2));
	}

	infile.close();
}

std::string LanguageLoader::getValue(std::string title) {
	std::map<std::string, std::string>::iterator found = _loaded.find(title);

	if (found != _loaded.end()) {
		return found->second;
	}

	return "";
}
