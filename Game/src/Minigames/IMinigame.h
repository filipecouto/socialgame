/**
 * IMinigame - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef IMINIGAME_H
#define IMINIGAME_H

#include <string>

class IMinigameInstance;
class GameContext;

/**
 * This class represents the definition of a mini-game
 * Each mini-game will create a MinigameInstance
 */
class IMinigame {
	public:
		/**
		 * Returns the internal name of this mini-game
		 * This may be used so the GameMod can store the right data about mini-games
		 */
		virtual std::string getInternalName() { return ""; }
		
		/**
		 * Returns the name of this mini-game
		 */
		virtual std::string getName() = 0;
		
		/**
		 * Returns the description of this mini-game
		 */
		virtual std::string getDescription() { return ""; }

		/**
		 * Loads any resources this mini-game needs in order to work
		 */
		virtual void load() { }

		/**
		 * Creates an instance of this mini-game
		 */
		virtual IMinigameInstance * newGame() = 0;
};

#endif
