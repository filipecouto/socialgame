/**
 * IPendingGame - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2014
 */

#ifndef IPENDINGGAME_H
#define IPENDINGGAME_H

#include <string>
#include <vector>

#include "ITag.h"
#include "IPerson.h"

class IMinigame;
class IMinigameFactory;
class IMinigameInstance;
class ITagsList;
class IPerson;

class IPendingGame {
	public:
		virtual IMinigame * getMinigame(int index, IMinigameFactory * factory) = 0;
		virtual int getMinigameLevel(int index) = 0;
		virtual int getMinigameCount() = 0;
		
		virtual bool setMinigameScore(int index, int score) = 0;
		
		virtual IConnection * getConnection() = 0;
};

#endif
