#ifndef ADVANCEDMODE_TAGSLIST_H
#define ADVANCEDMODE_TAGSLIST_H

#include "../../Models/ITagsList.h"

namespace AdvancedMode {
	class Cache;
	class Person;

	class TagsList : public ITagsList {
		public:
			TagsList(Person * person, Cache * cache);

			void load(Person * person);

			virtual bool contains(ITag * item);
			virtual ITag * operator[](int index);
			virtual int size();

			~TagsList();

		private:
			Cache * cache;

			std::vector<ITag *> tags;
	};
}

#endif // ADVANCEDMODE_TAGSLIST_H
