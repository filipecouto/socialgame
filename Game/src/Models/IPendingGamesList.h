/**
 * IPendingGamesList - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2014
 */

#ifndef IPENDINGGAMESLIST_H
#define IPENDINGGAMESLIST_H

#include "IList.h"
#include "IPendingGame.h"

class IPendingGamesList : public IList<IPendingGame*> {
};

#endif
