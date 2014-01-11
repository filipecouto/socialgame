/**
 * IUser - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef IUSER_H
#define IUSER_H

#include <string>
#include <vector>

#include "IPerson.h"

class IUser {
	public:
		/**
		 * Gets the person that this user represents
		 */
		virtual IPerson * getPerson() = 0;
		
		/**
		 * Creates a connection between friendToAdd and "this" person.
		 * The connection may be accepted or not by friendToAdd.
		 */
		virtual void addFriend(IPerson * friendToAdd) { }
		
		/**
		 * Removes a connection between friendToRemove and "this" person.
		 * This will remove the connection from both sides.
		 */
		virtual void removeFriend(IPerson * friendToRemove) { }
};

#endif
