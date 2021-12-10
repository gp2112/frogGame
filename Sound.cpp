
#include "Sound.hpp"



Sound::Sound() {
	
}

void audio_callback(void *userdata, Uint8 *stream, int len) {
	
	if (audio_len ==0)
		return;
	
	len = ( len > audio_len ? audio_len : len );
	
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
	
	audio_pos += len;
	audio_len -= len;
}

void Sound::play_async() {
	SDL_AudioSpec want, have;
	SDL_AudioDeviceID dev;

	SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
	want.freq = 48000;
	want.format = AUDIO_F32;
	want.channels = 2;
	want.samples = 4096;
	want.callback = audio_callback; 

	dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
	if (dev == 0) {
	    SDL_Log("Failed to open audio: %s", SDL_GetError());
	}
	else if (have.format != want.format)  /* we let this one thing change. */
	    SDL_Log("We didn't get Float32 audio format.");
	    
	SDL_PauseAudioDevice(dev, 0); /* start audio playing. */
	SDL_Delay(5000); /* let the audio callback play some sound for 5 seconds. */
	SDL_CloseAudioDevice(dev);
}


void Sound::play(string path) {
	 std::thread sd(&Sound::play_async, this);
	
}