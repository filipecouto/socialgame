#include "TagsList.h"
#include "Cache.h"
#include "Person.h"

AdvancedMode::TagsList::TagsList(Person * person, Cache * cache) : cache(cache) {
	load(person);
}

void AdvancedMode::TagsList::load(AdvancedMode::Person * person) {
	tags.clear();
	
	rapidjson::Value & list = cache->getService()->getUserTags(person->getId());

	rapidjson::SizeType len = list.Size();

	for (rapidjson::SizeType i = 0; i < len; i++) {
		const rapidjson::Value & item = list[i];
		
		tags.push_back(cache->getUserTag(std::stoi(item.GetString())));
	}
}

bool AdvancedMode::TagsList::contains(ITag * item) {
	int len = size();

	for (int i = 0; i < len; i++) {
		if (item == tags[i]) return true;
	}

	return false;
}

ITag * AdvancedMode::TagsList::operator[](int index) {
	return tags[index];
}

int AdvancedMode::TagsList::size() {
	return tags.size();
}

AdvancedMode::TagsList::~TagsList() {

}
