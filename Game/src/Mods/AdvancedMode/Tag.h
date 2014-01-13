#ifndef ADVANCEDMODE_TAG_H
#define ADVANCEDMODE_TAG_H

#include "../../Models/ITag.h"

namespace AdvancedMode {
	class Cache;
	
	class Tag : public ITag {
		public:
			Tag(int id, Cache * cache);
			
			int getId();

			virtual std::string getName();

		private:
			Cache * cache;
			
			int id;
			std::string name;
	};
}

#endif // ADVANCEDMODE_TAG_H
