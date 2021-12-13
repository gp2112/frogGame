#ifndef MIXER_H
#define MIXER_H

#include <thread>
#include "Sound.hpp"
#include "constants.hpp"


class Mixer {

private:
	Sound *samples[SAMPLES_N];
	std::thread *threads[SAMPLES_N];
	bool detach_mutex=false;
	bool *quit;

public:
	Mixer(bool *_quit);
	bool play(int song_id);
	void verify();
	std::thread verify_th;
};


#endif