#ifndef MINIGAMEFACTORY_H
#define MINIGAMEFACTORY_H
#include <vector>
#include "../GameContext.h"

class IMinigame;

class MinigameFactory {
	public:
		MinigameFactory();
		
		std::vector<IMinigame*> getMinigames(GameContext * context);
		
		~MinigameFactory();
};

#endif // MINIGAMEFACTORY_H
