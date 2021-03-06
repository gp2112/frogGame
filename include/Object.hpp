#ifndef OBJECT_H
#define OBJECT_H

#ifndef __linux__
	#include "SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

#include "constants.hpp"
#include "AnimationController.hpp"

class Object {
	int x, y, h, w;
	int dirX, dirY;
	int margin;
	double speed_x, speed_y;
	double ac_x=0, ac_y=0;
	bool wall;
	AnimationController* animationController;
	SDL_Texture* texture;

public:
	Object(int x0, int y0, int h0, int w0, bool wa, double sx, double sy, AnimationController* anim, SDL_Texture* tx);
	void move();
	void update();
	int getX();
	int getY();
	int getH();
	int getW();
	double getSpeedX();
	double getSpeedY();
	void setDir(int _x, int _y);
	SDL_Texture* getTexture();
	AnimationController* getAnimationController();
	void setSpeed(double _x, double _y);
	void setAceleration(double _x, double _y);
	void setPosition(int _x, int _y);
	void setSize(int _w, int _h);
	void setTexture(SDL_Texture* t);
	bool isOut();
	int getDirX();
	int getDirY();
	double dist(Object *obj);
};

class Player : public Object {
	bool is_hit;
	int hp;

public:
	Player(int x0, int y0, int h0, int w0, bool wa, double sx, double sy, AnimationController* anim, SDL_Texture* tx);
	//void hit();
	//bool isHit();
	//void unhit();
	bool getDamage();
	int getHp();
	void setHp(int hp0);
};


#endif
