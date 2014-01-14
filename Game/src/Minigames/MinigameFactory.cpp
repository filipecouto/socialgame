#include "MinigameFactory.h"

#include "Hangman/Hangman.h"
#include "Maze/MazeMinigame.h"
#include "TicTacToe/TicTacToe.h"

MinigameFactory::MinigameFactory(GameContext * context) : context(context) {

}

IMinigame * MinigameFactory::getMinigame(const string internalName) {

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
