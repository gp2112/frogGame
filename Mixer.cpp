#include <cstring>
#include <iostream>
#include "Mixer.hpp"


/*

O Mixer organiza os sons do jogo através da criação de uma thread para cada som.

o array "samples" armazena classes Sound correspondentes a cada som do jogo.
o array "threads" armazena as threads de cada som que está tocando.

Ao chamar o método "play", o programa vai verificar se esse som já está sendo executado em uma thread.
Caso já esteja, é finalizado para executar outra.

antes, porém, é utilizado um semáforo mutex para impedir que seja acessado uma area da memória correspondente à que está sendo 
analisada pelo método de verificação.

o método "verify" é chamado em uma outra thread para verificar se algum som já foi executado, i.e. se a thread já foi finalizada.
Caso já tenha sido, ela é excluída.




*/


Mixer::Mixer(bool *_quit) {
	quit=_quit;
	memset(samples, 0, sizeof(samples));
	memset(threads, 0, sizeof(threads));
	samples[SAMPLE_FROG] = new Sound("sound/frog_collect.wav");
	samples[SAMPLE_COL] = new Sound("sound/damage.wav");
	verify_th = std::thread(&Mixer::verify, this);
}

bool Mixer::play(int song_id) {
	if (song_id > SAMPLES_N || samples[song_id]==NULL)
		return false;
	
	while (detach_mutex);
	if (threads[song_id] != NULL) {
		detach_mutex = true;
		D std::cout << samples[song_id]->path << " already playing" << std::endl;
		samples[song_id]->stop();
		samples[song_id]->restart();
		threads[song_id]->detach();
		delete threads[song_id];
		threads[song_id] = NULL;
		detach_mutex = false;
	}
	
	threads[song_id] = new std::thread(&Sound::play, samples[song_id]);

	return true;
}

void Mixer::verify() {
	while (!(*quit)) {
		D std::cout << "verifying..." << std::endl;
		for (int i=0; i<SAMPLES_N; i++) {

			while (detach_mutex); // proíbe o acesso enquanto o método "play" estiver utilizando a mesma região de memória
			if (threads[i]!=NULL)
				if (samples[i]->isOver()) {
					detach_mutex = true;
					std::cout << "over" << std::endl;
					samples[i]->stop();
					samples[i]->restart();
					threads[i]->detach();
					if (threads[i]==NULL)
						D std::cout << "free===========" << std::endl;
					delete threads[i];
					threads[i] = NULL;
					detach_mutex = false;
				}
		}

		SDL_Delay(100);
	}

	// quando o jogo para, libera todos os áudios
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
