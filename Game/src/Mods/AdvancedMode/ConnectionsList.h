#ifndef ADVANCEDMODE_CONNECTIONSLIST_H
#define ADVANCEDMODE_CONNECTIONSLIST_H

#include "../../Models/IConnectionsList.h"

class CentralServerWebService;
class IMoodsList;

namespace AdvancedMode {
	class Cache;
	class MoodsList;
	class Person;
	
	class ConnectionsList : public IConnectionsList {
		public:
			ConnectionsList(Person * from, Cache * cache);
			
			virtual int getFriendsCount();
			virtual bool isFriendsWith(IPerson * person);
			
			virtual int size();
			virtual bool contains(IConnection * item);
			virtual IConnection * operator[](int index);

		private:
			Cache * cache;
			
			std::vector<IConnection *> connections;
	};
}

#endif // ADVANCEDMODE_CONNECTIONSLIST_H

class CentralServerWebService;
