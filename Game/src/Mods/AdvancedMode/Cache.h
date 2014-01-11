#ifndef ADVANCEDMODE_CACHE_H
#define ADVANCEDMODE_CACHE_H

#include <vector>
#include "CentralServerWebService.h"

class IPerson;
namespace AdvancedMode {
	class Person;
	class MoodsList;
	
	class Cache {
		public:
			Cache(CentralServerWebService * service, MoodsList * moods);
			
			CentralServerWebService * getService();
			
			IPerson * getPerson(int id);
			
			MoodsList * getMoods();

			~Cache();

		private:
			CentralServerWebService * service;

			MoodsList * moods;
			
			std::vector<Person *> people;
	};
}

#endif // ADVANCEDMODE_CACHE_H
