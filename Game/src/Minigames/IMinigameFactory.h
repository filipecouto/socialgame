#ifndef IMINIGAMEFACTORY_H
#define IMINIGAMEFACTORY_H

#include <vector>
#include <string>

class GameContext;
class IMinigame;

class IMinigameFactory {
	public:
		virtual IMinigame* getMinigame(const std::string internalName) = 0;
		
		virtual std::vector<IMinigame*> getMinigames() = 0;
};

#endif // IMINIGAMEFACTORY_H
