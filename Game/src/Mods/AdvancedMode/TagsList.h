#ifndef ADVANCEDMODE_TAGSLIST_H
#define ADVANCEDMODE_TAGSLIST_H

#include "../../Models/ITagsList.h"
#include "CentralServerWebService.h"

namespace AdvancedMode {
	class Person;
	
	class TagsList : public ITagsList {
		public:
			TagsList(Person * person, CentralServerWebService * service);

			virtual bool contains(Tag & item);
			virtual Tag & operator[](int index);
			virtual int size();

			~TagsList();

		private:
			CentralServerWebService * service;
	};
}

#endif // ADVANCEDMODE_TAGSLIST_H
