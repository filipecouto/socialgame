#include "MinigameFactory.h"

#include "Hangman/Hangman.h"
#include "Maze/MazeMinigame.h"
#include "TicTacToe/TicTacToe.h"

MinigameFactory::MinigameFactory() {

}

std::vector< IMinigame * > MinigameFactory::getMinigames(GameContext * context) {
	std::vector<IMinigame *> result;
	result.push_back(new HangmanMinigame(context));
	result.push_back(new MazeMinigame(context));
	result.push_back(new TicTacToeMinigame(context));

	return result;
}

MinigameFactory::~MinigameFactory() {

}
