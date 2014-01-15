#ifndef SM_CONNECTIONSLIST_H
#define SM_CONNECTIONSLIST_H
#include "../../Models/IConnectionsList.h"
#include "SimpleMode.h"

namespace SimpleMode {
	class ConnectionsList : public IConnectionsList {

		public:
			ConnectionsList();
			virtual ~ConnectionsList();
			virtual bool contains(IConnection * item);
			virtual IConnection * getConnectionWith(IPerson * person);
			virtual int getFriendsCount();
			virtual bool isFriendsWith(IPerson * person);
			virtual IConnection * operator[](int index);
			virtual int size();
			virtual void addConnection(IConnection * connection);
		private:
			std::vector<IConnection *> connections;
	};
}
#endif // CONNECTIONSLIST_H
