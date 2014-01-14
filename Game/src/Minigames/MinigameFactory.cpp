#ifdef _WIN32
#include <windows.h>
#endif

#include "MinigameFactory.h"

#include "Hangman/Hangman.h"
#include "Maze/MazeMinigame.h"
#include "TicTacToe/TicTacToe.h"

MinigameFactory::MinigameFactory(GameContext * context) : context(context) {

}

IMinigame * MinigameFactory::getMinigame(const string internalName) {
	std::vector<IMinigame*> minigames = getMinigames();
	
	for(int i = 0; i < minigames.size(); i++) {
		if(internalName == minigames[i]->getInternalName()) return minigames[i];
	}
	
	return NULL;
}

std::vector< IMinigame * > MinigameFactory::getMinigames() {
	std::vector<IMinigame *> result;
	result.push_back(new HangmanMinigame(context));
	result.push_back(new MazeMinigame(context));
	result.push_back(new TicTacToeMinigame(context));

	return result;
}

MinigameFactory::~MinigameFactory() {

}
