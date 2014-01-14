#ifndef ISOUND_H
#define ISOUND_H

#include <alut.h>
#include <string>

class Sound {

	typedef struct {
		ALuint buffer, source;
		ALboolean key_s;
	} State;

	public:
		State state;

		Sound();

		void initAudio();

		~Sound();
};

#endif
