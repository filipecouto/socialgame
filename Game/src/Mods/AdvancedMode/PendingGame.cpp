#include "PendingGame.h"
#include "dependencies/rapidjson/document.h"
#include "../../Minigames/IMinigameFactory.h"

using namespace AdvancedMode;

PendingGame::PendingGame(const rapidjson::Value & data, Cache * cache) {
	connectionId = std::stoi(data["connectionId"].GetString());
	gameId = std::stoi(data["gameId"].GetString());
	game = data["gameName"].GetString();
	level = std::stoi(data["level"].GetString());
}

IConnection * PendingGame::getConnection() {
	return NULL;
}

bool PendingGame::setMinigameScore(int score) {
	return true;
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
