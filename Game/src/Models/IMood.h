/**
 * IMood - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef IMOOD_H
#define IMOOD_H

#include <string>

class IMood {
	public:
		virtual std::string getDescription() = 0;
};

#endif
