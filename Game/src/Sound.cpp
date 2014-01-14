#include "Sound.h"

Sound::Sound(){

}

void Sound::initAudio(){
	state.buffer = alutCreateBufferFromFile("BG001.wav");
	alGenSources(1, &state.source);
	alSourcei(state.source, AL_BUFFER, state.buffer);
	alSourcei(state.source, AL_LOOPING, AL_TRUE);
}

Sound::~Sound(){

}