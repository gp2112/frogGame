#ifndef SOUND_H
#define SOUND_H

#ifndef __linux__
	#include "SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

#include "constants.hpp"

class Sound {

private:


public:
	std::string path;
	SDL_AudioSpec wav_specs;
	Uint32 audio_len, audio_len_miss;
	Uint8 *wav_buffer, *audio_pos;
	Sound(std::string _path);
	void stop();
	void pause();
	void free();
	void resume();
	bool play();
	void restart();
	bool isOver();

};


#endif