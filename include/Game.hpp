#ifndef GAME_H
#define GAME_H

#include "Graphics.hpp"
#include "Object.hpp"
#include "Mixer.hpp"

#include <list>
#include <thread>

using namespace std;
class Game {

private:
	int points=0;
	bool pause = false;
	bool quit = false;
	thread t_input;
	Graphics* graphics;
	Mixer *mixer;
	SDL_Event event;
	Object* player;
	list<Object*> frogs;
	void setupPlayer();
	void getInput();
	void createFrog();
	void removeFrog(list<Object*>::iterator k);
	void moveFrogs();
	void keyPressed(SDL_Keycode key, bool down);

public:
	Game();
	void play();

};



#endif