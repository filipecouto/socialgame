#include "Tag.h"
#include "Cache.h"

using namespace AdvancedMode;

Tag::Tag(int id, Cache * cache) : id(id), cache(cache) {
	name = cache->getService()->getTag(id)["name"].GetString();
}

int Tag::getId() {
	return id;
}

std::string Tag::getName() {
	return name;
}
