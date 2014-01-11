#ifndef ADVANCEDMODE_USER_H
#define ADVANCEDMODE_USER_H

#include "../../Models/IUser.h"
#include "CentralServerWebService.h"
#include "MoodsList.h"

namespace AdvancedMode {
	class Cache;
	
	class User : public IUser {
		public:
			User(Cache * cache);

			virtual IPerson * getPerson();
			virtual void addFriend(IPerson * friendToAdd);

			~User();

		private:
			Cache * cache;

			int id;
			IPerson * person = NULL;
	};
}

#endif // ADVANCEDMODE_USER_H
