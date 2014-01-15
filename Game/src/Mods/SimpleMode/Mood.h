#ifndef SM_MOOD_H
#define SM_MOOD_H
#include "../../Models/IMood.h"
#include "SimpleMode.h"

namespace SimpleMode {
	class Mood : public IMood {

		public:
			Mood(std::string description);
			virtual ~Mood();
			virtual std::string getDescription();
		private:
			int id;
			std::string description;

	};
}
#endif // MOOD_H
