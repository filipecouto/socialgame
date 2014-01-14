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
		virtual ~LanguageLoader();
		std::vector<Language> getLanguages();
		void setLanguage(Language language);
		string getValue(string title);
	private:
		std::vector<Language> _languages;
		std::map<string,string> _loaded;
		
		std::vector<Language> loadLanguages();
};

#endif // LANGUAGELOADER_H
