#ifndef ADVANCEDMODE_CACHE_H
#define ADVANCEDMODE_CACHE_H

#include <vector>
#include "CentralServerWebService.h"

class IConnection;
class IPerson;

namespace AdvancedMode {
	class Connection;
	class Person;
	class MoodsList;
	
	class Cache {
		public:
			Cache(CentralServerWebService * service, MoodsList * moods);
			
			CentralServerWebService * getService();
			
			void setIdentityPerson(IPerson * person);
			IPerson * getIdentityPerson();
			
			IPerson * getPerson(int id);
			
			MoodsList * getMoods();

			~Cache();

		private:
			CentralServerWebService * service;
			
			IPerson * identityPerson;

			MoodsList * moods;
			
			std::vector<Person *> people;
			std::vector<Connection *> connections;
	};
}

#endif // ADVANCEDMODE_CACHE_H
