#include "PendingGame.h"
#include "dependencies/rapidjson/document.h"
#include "Connection.h"
#include "Cache.h"
#include "Person.h"
#include "../../Minigames/IMinigameFactory.h"

using namespace AdvancedMode;

PendingGame::PendingGame(const rapidjson::Value & data, Cache * cache) : cache(cache) {
	connectionId = std::stoi(data["connectionId"].GetString());
	gameId = std::stoi(data["gameId"].GetString());
	game = data["gameName"].GetString();
	level = std::stoi(data["level"].GetString());
}

IConnection * PendingGame::getConnection() {
	if (!connection) {
		const rapidjson::Value & data = cache->getService()->getConnection(connectionId);

		if (data.IsArray()) connection = new Connection(((Person *)cache->getIdentityPerson())->getId(), data[rapidjson::SizeType(0)], cache);
	}

	return connection;
}

bool PendingGame::setMinigameScore(int score, int index) {
	if (cache->getService()->setGameScore(connectionId, gameId, score)) {
		return true;
	} else {
		return false;
	}
}

int PendingGame::getMinigameCount() {
	return 1;
}

int PendingGame::getMinigameLevel(int index) {
	return level;
}

IMinigame * PendingGame::getMinigame(int index, IMinigameFactory * factory) {
	return factory->getMinigame(game);
}
