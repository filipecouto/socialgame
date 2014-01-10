/**
 * IMoodsList - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef IMOODSLIST_H
#define IMOODSLIST_H

#include "IList.h"
#include "IPerson.h"

class IMoodsList : public IList<IMood*> {
	public:
		virtual ~IMoodsList() { }
};

#endif
