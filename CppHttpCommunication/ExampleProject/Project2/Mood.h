/**
 * Mood - Header
 *
 * This code is part of the game module of the Social Game.
 *
 * CrossWeb Enterprise - 2013
 */

#ifndef MOOD_H
#define MOOD_H

#include <string>

class Mood {
	public:
		Mood();
		Mood(std::string description);

		std::string getDescription();
		void setDescription(std::string description);

		virtual ~Mood();

	private:
		std::string _description;
};

#endif
