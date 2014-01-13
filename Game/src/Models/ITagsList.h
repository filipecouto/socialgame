/**
 * ITagsList - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef ITAGSLIST_H
#define ITAGSLIST_H

#include "IList.h"
#include "IPerson.h"

class ITagsList : public IList<ITag*> {
	public:
		virtual ~ITagsList() { }
};

#endif
