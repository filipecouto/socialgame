#include "Sound.h"

Sound::Sound() {
}

Sound::Sound(std::string filename) {
	loadSoundFile(filename);
	_volume = 0.5f;
}

void Sound::initAudio() {
	printf("%s\n", filename.c_str());
	_state.buffer = alutCreateBufferFromFile(filename.c_str());
	alGenSources(1, &_state.source);
	changeVolume();
	alSourcei(_state.source, AL_BUFFER, _state.buffer);
	_state.key_s = AL_FALSE;
	alSourcePlay(_state.source);
}

bool Sound::loadSoundFile(std::string filename) {
	this->filename = filename;
	return true;
}

Sound::~Sound() {
	ALCcontext * context = alcGetCurrentContext();
	ALCdevice * device = alcGetContextsDevice(context);
	alcCloseDevice(device);
	alDeleteBuffers(1, &_state.buffer);
	alDeleteSources(1, &_state.source);
}

void Sound::setVolume(float volume) {
	_volume = volume;
	changeVolume();
}

void Sound::changeVolume() {
	alSourcef(_state.source, AL_GAIN, _volume);
}
