#include "Sound.h"

Sound::Sound(){

}

Sound::Sound(std::string filename){
	loadSoundFile(filename);
}

void Sound::initAudio(){
	printf("%s\n", filename.c_str());
	state.buffer = alutCreateBufferFromFile(filename.c_str());
	alGenSources(1, &state.source);
	alSourcei(state.source, AL_BUFFER, state.buffer);
	state.key_s = AL_FALSE;
	alSourcePlay(state.source);
}

bool Sound::loadSoundFile(std::string filename){
	this->filename = filename;
	return true;
}

Sound::~Sound(){

}