#ifndef FRIENDSLIST_H
#define FRIENDSLIST_H

#include <vector>
#include "../../Models/IList.h"
#include "../../Models/IConnectionsList.h"
#include "Connection.h"

class FriendsList : public IConnectionsList, private std::vector<IConnection*> {
	public:
		IConnection* operator[](int index) {
			return std::vector<IConnection*>::operator[](index);
		}

		bool contains(IConnection* item) {
			int len = size();

			for (int i = 0; i < len; i++) {
				if (item == operator[](i)) return true;
			}

			return false;
		}

		int size() {
			return std::vector<IConnection*>::size();
		}
		
		virtual int getFriendsCount();
		
		virtual IConnection * getConnectionWith(IPerson * person);
		virtual bool isFriendsWith(IPerson * person);
		
		bool hasFriend(IPerson * person);

		void add(IConnection* item) {
			std::vector<IConnection*>::push_back(item);
		}
};

#endif // FRIENDSLIST_H
