/**
 * IConnectionsList - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef ICONNECTIONSLIST_H
#define ICONNECTIONSLIST_H

#include "IList.h"
#include "IConnection.h"
#include "IPerson.h"

class IConnectionsList : public IList<IConnection*> {
	public:
		virtual bool isFriendsWith(IPerson * person) = 0;
		
		virtual int getFriendsCount() = 0;

		virtual ~IConnectionsList() { }
};

#endif
