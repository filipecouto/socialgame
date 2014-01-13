#include "Tag.h"

using namespace AdvancedMode;

Tag::Tag(int id, Cache * cache) : id(id), cache(cache) {
	printf("new Tag(%d)\n", id);
	name = "tag";
}

int Tag::getId() {
	return id;
}

std::string Tag::getName() {
	return name;
}
