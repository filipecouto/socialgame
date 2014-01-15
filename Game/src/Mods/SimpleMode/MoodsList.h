#ifndef SM_MOODSLIST_H
#define SM_MOODSLIST_H
#include "../../Models/IMoodsList.h"
#include "SimpleMode.h"

namespace SimpleMode {
	class MoodsList : public IMoodsList {
		public:
			MoodsList();
			virtual ~MoodsList();
			virtual bool contains(IMood * item);
			virtual IMood * operator[](int index);
			virtual int size();
			virtual void addMood(IMood *);
		private:
			std::vector<IMood *> moods;
	};
}

#endif // MOODSLIST_H
