#ifndef GAME_H
#define GAME_H

#include "Graphics.h"

#include <list>

class Game {

private:
	int points;
	bool is_paused;
	Graphics *graphics;
	std::list<Object *> sapos;

public:



};



#endif