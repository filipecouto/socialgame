#ifndef ADVANCEDMODE_PERSON_H
#define ADVANCEDMODE_PERSON_H

#include "../../Models/IPerson.h"
#include "dependencies/rapidjson/document.h"
#include "CentralServerWebService.h"
#include "MoodsList.h"

namespace AdvancedMode {
	class Cache;
	
	class Person : public IPerson {
		public:
			Person(int id, Cache * cache);
			Person(const rapidjson::Value & data, Cache * cache);

			virtual int getId();

			virtual IConnectionsList * getConnections();
			virtual ITagsList * getTags();

			virtual std::string getName();
			virtual int getStrength();
			virtual int getScore();
			
			virtual IMood * getMood();
			void setMood(IMood * mood);

			~Person();

		private:
			Cache * cache;

			int id;
			std::string name;
			int score, strength;
			IMood * mood = NULL;

			IConnectionsList * connections = NULL;
	};
}

#endif // ADVANCEDMODE_PERSON_H
