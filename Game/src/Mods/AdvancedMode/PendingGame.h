#ifndef ADVANCEDMODE_PENDINGGAME_H
#define ADVANCEDMODE_PENDINGGAME_H

#include "../../Models/IPendingGame.h"
#include "dependencies/rapidjson/document.h"

class IMinigame;
class IMinigameFactory;

namespace AdvancedMode {
	class Cache;
	class PendingGame : public IPendingGame {
		public:
			PendingGame(const rapidjson::Value & data, Cache * cache);
			
			virtual IConnection * getConnection();
			
			virtual int getMinigameCount();
			virtual int getMinigameLevel(int index);
			virtual IMinigame * getMinigame(int index, IMinigameFactory * factory);
			
			virtual bool setMinigameScore(int score);
			
		private:
			Cache * cache;
			
			int connectionId, gameId;
			int level;
			std::string game;
	};
}

#endif // ADVANCEDMODE_PENDINGGAME_H

class IMinigame;
