/**
 * IMinigameInstance - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef IMINIGAMEINSTANCE_H
#define IMINIGAMEINSTANCE_H

#include "../GameFragment.h"

class IMinigameInstance : public GameFragment {
	public:
		/**
		 * Called when the game has everything ready to display this mini-game
		 */
		virtual void start(int level) = 0;
		
		/**
		 * Called when the user pauses the game
		 * This can happen when the user, for instance, interacts with the GUI to
		 * do something that distracts the user from the mini-game.
		 */
		virtual void pause() { }
		
		/**
		 * Called by the instance itself when the game is over or by what runs it
		 * If needed, any final animations should happen here and, once they
		 * finish, the instance should notify what runs it that it is done.
		 */
		virtual void finish() = 0;
		
		/**
		 * The score earned with this game, this is going to be stored in user's account
		 */
		virtual int getScore() { return 0; }
};

#endif
