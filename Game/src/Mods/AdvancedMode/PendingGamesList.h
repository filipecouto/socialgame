#ifndef ADVANCEDMODE_PENDINGGAMESLIST_H
#define ADVANCEDMODE_PENDINGGAMESLIST_H

#include "../../Models/IPendingGamesList.h"
#include "Cache.h"

namespace AdvancedMode {

	class PendingGamesList : public IPendingGamesList {
		public:
			PendingGamesList(Cache * cache);

			virtual int size();
			virtual bool contains(IPendingGame * item);
			virtual IPendingGame * operator[](int index);

		private:
			Cache * cache;
			
			std::vector<IPendingGame *> games;
			
			void load();
	};
}

#endif // ADVANCEDMODE_PENDINGGAMESLIST_H
