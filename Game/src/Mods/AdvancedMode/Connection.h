#ifndef ADVANCEDMODE_CONNECTION_H
#define ADVANCEDMODE_CONNECTION_H

#include "../../Models/IConnection.h"
#include "dependencies/rapidjson/document.h"

class IMoodsList;
class CentralServerWebService;

namespace AdvancedMode {
	class Cache;
	class MoodsList;
	
	class Connection : public IConnection {
		public:
			Connection(const rapidjson::Value & data, Cache * cache);

			virtual int getScore();
			virtual int getStrength();
			virtual int getState();
			virtual IPerson * getPerson();

		private:
			Cache * cache;
			
			int id;
			int personId;
			IPerson * person = NULL;
			int score, strength, state;
	};
}

#endif // ADVANCEDMODE_CONNECTION_H
