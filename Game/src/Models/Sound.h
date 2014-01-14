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
		std::string filename;

		Sound();
		Sound(std::string filename);

		void initAudio();
		bool loadSoundFile(std::string filename);
		void setVolume(float volume);
		void changeVolume();

		~Sound();
		
	private:
		float _volume;
		State _state;
};

#endif
