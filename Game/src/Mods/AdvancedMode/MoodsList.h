#ifndef ADVANCEDMODE_MOODSLIST_H
#define ADVANCEDMODE_MOODSLIST_H

#include "../../Models/IMoodsList.h"
#include "CentralServerWebService.h"

namespace AdvancedMode {
	class MoodsList : public IMoodsList {
		public:
			MoodsList(const rapidjson::Value & data, CentralServerWebService * service);

			virtual IMood * getMoodByID(int id);
			
			virtual bool contains(IMood * item);
			virtual IMood * operator[](int index);
			virtual int size();

			~MoodsList();
			
		private:
			CentralServerWebService * service;
			
			std::vector<IMood *> moods;
	};
}

#endif // ADVANCEDMODE_MOODSLIST_H
