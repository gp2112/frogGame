#include <cstring>
#include <iostream>
#include "Mixer.hpp"


Mixer::Mixer(bool *_quit) {
	quit=_quit;
	memset(samples, 0, sizeof(samples));
	memset(threads, 0, sizeof(threads));
	samples[SAMPLE_COL] = new Sound("sound/HIT.wav");
	verify_th = std::thread(&Mixer::verify, this);
}

bool Mixer::play(int song_id) {
	if (song_id > SAMPLES_N || samples[song_id]==NULL)
		return false;
	
	if (threads[song_id] != NULL) {
		D std::cout << samples[song_id]->path << " already playing" << std::endl;
		samples[song_id]->restart();
	}

	else
		threads[song_id] = new std::thread(&Sound::play, samples[song_id]);

	return true;
}

void Mixer::verify() {
	while (!(*quit)) {
		D std::cout << "verifying..." << std::endl;
		for (int i=0; i<SAMPLES_N; i++) {
			if (threads[i]!=NULL)
				if (samples[i]->isOver()) {
					//std::cout << "over" << std::endl;
					samples[i]->restart();
					threads[i]->detach();
					delete threads[i];
					threads[i] = NULL;
				}
		}

		SDL_Delay(100);
	}

	// when the game stops, release all audios
	for (int i=0; i<SAMPLES_N; i++) {
		if (threads[i]!=NULL) {
			delete threads[i];
			threads[i] = NULL;
		}
		if (samples[i]!=NULL) {
			samples[i]->free();
			delete samples[i];
			samples[i] = NULL;
		}
	}

}
