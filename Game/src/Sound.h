#ifndef ISOUND_H
#define ISOUND_H

#ifdef _WIN32
#include <alut.h>
#else
#include <AL/al.h>
#include <AL/alut.h>
#endif
#include <string>

class Sound {
	typedef struct {
		ALuint buffer, source;
		ALboolean key_s;
	} State;

	public:

		Sound();

		void initAudio();
		void setVolume(float volume);
		void play();

		~Sound();

	private:
		float _volume;
		State _state;
		std::string _filename;
		
		void changeVolume();
};

#endif
