#ifndef MOOD_H
#define MOOD_H

#include "../../Models/IMood.h"

class Mood : public IMood {
	public:
		Mood(std::string name);

		virtual std::string getDescription();

		~Mood();

	private:
		std::string mood;
};

#endif // MOOD_H
