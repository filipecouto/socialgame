#ifndef ADVANCEDMODE_MOOD_H
#define ADVANCEDMODE_MOOD_H

#include "../../Models/IMood.h"

namespace AdvancedMode {
	class Mood : public IMood {
		public:
			Mood(int id, std::string description);

			virtual int getId();
			virtual std::string getDescription();

			~Mood();

		private:
			int id;
			std::string description;
	};
}

#endif // ADVANCEDMODE_MOOD_H
