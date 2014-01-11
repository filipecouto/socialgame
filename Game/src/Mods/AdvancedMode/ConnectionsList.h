#ifndef ADVANCEDMODE_CONNECTIONSLIST_H
#define ADVANCEDMODE_CONNECTIONSLIST_H

#include "../../Models/IConnectionsList.h"

class CentralServerWebService;
class IMoodsList;

namespace AdvancedMode {
	class Person;
	class Cache;
	class MoodsList;
	class Person;
	
	class ConnectionsList : public IConnectionsList {
		public:
			ConnectionsList(Person * from, Cache * cache);
			
			void loadList();
			
			virtual int getFriendsCount();
			virtual bool isFriendsWith(IPerson * person);
			virtual IConnection * getConnectionWith(IPerson * person);
			
			virtual void removeConnection(IPerson * person);
			
			virtual int size();
			virtual bool contains(IConnection * item);
			virtual IConnection * operator[](int index);

		private:
			Cache * cache;
			Person * from;
			
			std::vector<IConnection *> connections;
	};
}

#endif // ADVANCEDMODE_CONNECTIONSLIST_H

class CentralServerWebService;
