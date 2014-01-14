#ifndef LANGUAGE_H
#define LANGUAGE_H
#include <string>

class Language {

	public:
		Language(std::string name, std::string path);
		virtual ~Language();
		
		std::string getName();
		std::string getPath();
	private:
		std::string _name;
		std::string _path;

};

#endif // LANGUAGE_H
