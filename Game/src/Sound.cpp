#include "Sound.h"

Sound::Sound() {
	_volume = 1.0f;
}

void Sound::initAudio() {
	_filename = "BG001.wav";
	printf("%s\n", _filename.c_str());
	_state.buffer = alutCreateBufferFromFile(_filename.c_str());
	alGenSources(1, &_state.source);
	changeVolume();
	alSourcei(_state.source, AL_BUFFER, _state.buffer);
	alSourcei(_state.source, AL_LOOPING,  AL_TRUE);
	_state.key_s = AL_FALSE;
	alSourcePlay(_state.source);
}

void Sound::setVolume(float volume) {
	_volume = volume;
	changeVolume();
}

void Sound::changeVolume() {
	alSourcef(_state.source, AL_GAIN, _volume);
}

Sound::~Sound() {
	ALCcontext * context = alcGetCurrentContext();
	ALCdevice * device = alcGetContextsDevice(context);
	alcCloseDevice(device);
	alDeleteBuffers(1, &_state.buffer);
	alDeleteSources(1, &_state.source);
}
