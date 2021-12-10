#ifndef SOUND_H
#define SOUND_H

#ifndef __linux__
	#include "SDL_mixer.h"
#else
	#include <SDL2/SDL_audio.h>
#endif

#include <thread>

class Sound {

private:
	Uint32 wav_length;
	Uint8 *wav_buffer; 
	SDL_AudioSpec wav_spec;
	std::thread threads;
	int thread_n;

public:
	Sound();
	void play(string path);

}


#endif