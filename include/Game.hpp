#ifndef GAME_H
#define GAME_H

#include "Graphics.hpp"
#include "Object.hpp"

#include <list>
using namespace std;
class Game {

private:
	int points;
	bool is_paused;
	bool quit = false;
	Graphics* graphics;
	list<Object*> frogs;
	SDL_Event event;
	void setupPlayer();
	void createFrog();
	Object* player;

public:
	Game();
	void play();

};



#endif