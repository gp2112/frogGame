#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include "constants.h"

class Object {
	int x, y, h, w;
	double speed_x, speed_y;
	bool wall;
	SDL_Texture *texture;
	AnimationController *animationController;

public:
	Object(int x0, int y0, int h0, int w0, bool wa);
	void move();
	int getx();
	int gety();
	int geth();
	int getw();
	double getSpeed();
	SDL_Texture *getTexture();
	void setSpeed(double sp);
	void setx(int x0);
	void sety(int y0);
	void setH(int h0);
	void setW(int w0);
	void setTexture(SDL_Texture *t);
	bool isOut();

class Player: public Object {
	bool is_hit;
	int hp;

public:
	Player(int x0, int y0);
	void hit();
	bool isHit();
	void unhit();
	int getHp();
	void setHp(int hp0);
};


#endif
