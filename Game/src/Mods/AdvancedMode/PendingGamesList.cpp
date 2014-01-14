#include "PendingGamesList.h"
#include "PendingGame.h"

using namespace AdvancedMode;

PendingGamesList::PendingGamesList(Cache * cache) : cache(cache) {
	load();
}

int PendingGamesList::size() {
	return games.size();
}

bool PendingGamesList::contains(IPendingGame * item) {
	return false;
}

IPendingGame * PendingGamesList::operator[](int index) {
	return games[index];
}

void PendingGamesList::load() {
	const rapidjson::Value & list = cache->getService()->getPendingGames();

	if (list.IsArray()) {
		rapidjson::SizeType len = list.Size();

		for (rapidjson::SizeType i = 0; i < len; i++) {
			const rapidjson::Value & item = list[i];

			games.push_back(new PendingGame(item, cache));
		}
	}
}
