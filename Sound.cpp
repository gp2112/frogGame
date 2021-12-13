#include <iostream>
#include "Sound.hpp"


Sound::Sound(std::string _path) {
	path = _path;


	if (SDL_LoadWAV(path.c_str(), &wav_specs, &wav_buffer, &audio_len)==NULL) {
		std::cout << "Could not open sound file: " << _path << std::endl;	
		std::cout << SDL_GetError() << std::endl;
	}
	
	audio_pos = wav_buffer;
	audio_len_miss = audio_len;

}


void audio_callback(void *userdata, Uint8 *stream, int len) {

	Sound *sound = (Sound *)userdata;

	D std::cout << 100 - 100*(double)((double)sound->audio_len_miss/(double)sound->audio_len) << "%" << std::endl;

	if (sound->audio_len_miss <= 0) {
		D std::cout << "stopped" << std::endl;
		return; 
	}
	
	len = ( len > sound->audio_len_miss ? sound->audio_len_miss : len );
	
	SDL_memset(stream, 0, len);
	SDL_MixAudio(stream, sound->audio_pos, len, SDL_MIX_MAXVOLUME);
	sound->audio_pos += len;
	sound->audio_len_miss -= len;
}


bool Sound::play() {
	if (is_open)
		return true;

	wav_specs.callback = audio_callback;
	wav_specs.userdata = this;
	int r;


	if ((r=SDL_OpenAudio(&wav_specs, NULL)) < 0) {
		D std::cout << "Could not play song: "<< r << SDL_GetError()<< std::endl;
		return false;
	}
	is_open = true;

	SDL_PauseAudio(0);

	while (audio_len_miss > 0)
		SDL_Delay(100);
	
	D std::cout << "stopped playing audio" << std::endl;

	SDL_CloseAudio();
	is_open = false;

	return true;
	
}

void Sound::stop() {
	audio_len_miss = 0;
}

void Sound::restart() {
	audio_len_miss = audio_len;
	audio_pos = wav_buffer;
}

void Sound::free() {
	SDL_FreeWAV(wav_buffer);
}

void Sound::pause() {
	SDL_PauseAudio(1);
}

void Sound::resume() {
	SDL_PauseAudio(0);
}

bool Sound::isOver() {
	return audio_len_miss<=0;
}