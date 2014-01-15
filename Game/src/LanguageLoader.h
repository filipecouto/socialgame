#ifndef LANGUAGELOADER_H
#define LANGUAGELOADER_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include "Language.h"

class LanguageLoader {
	public:
		LanguageLoader();

		std::vector<Language> getLanguages();
		void setLanguage(Language language);
		std::string getValue(std::string title);

		virtual ~LanguageLoader();
	private:
		std::vector<Language> _languages;
		std::map<std::string, std::string> _loaded;

		std::vector<Language> loadLanguages();
};

#endif // LANGUAGELOADER_H
