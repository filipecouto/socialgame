#ifndef MINIGAMEFACTORY_H
#define MINIGAMEFACTORY_H

#include <vector>

#include "../GameContext.h"
#include "IMinigameFactory.h"

class IMinigame;

class MinigameFactory : public IMinigameFactory {
	public:
		MinigameFactory(GameContext * context);

		IMinigame * getMinigame(const std::string internalName);
		std::vector<IMinigame *> getMinigames();

		~MinigameFactory();

	private:
		GameContext * context;
};

#endif // MINIGAMEFACTORY_H
