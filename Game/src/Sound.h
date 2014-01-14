#ifndef ISOUND_H
#define ISOUND_H

#ifdef _WIN32
#include <alut.h>
#else
#include <AL/alut.h>
#endif
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
