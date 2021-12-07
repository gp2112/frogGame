#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include "constants.hpp"
#include "AnimationController.hpp"

class Object {
	int x, y, h, w;
	int dirX, dirY;
	double speed_x, speed_y;
	bool wall;
	AnimationController* animationController;
	SDL_Texture* texture;

public:
	Object(int x0, int y0, int h0, int w0, bool wa, int sx, int sy, AnimationController* anim, SDL_Texture* tx);
	void move();
	void update();
	int getX();
	int getY();
	int getH();
	int getW();
	int getSpeedX();
	int getSpeedY();
	void setDir(int _x, int _y);
	SDL_Texture* getTexture();
	AnimationController* getAnimationController();
	void setSpeed(int _x, int _y);
	void setPosition(int _x, int _y);
	void setSize(int _w, int _h);
	void setTexture(SDL_Texture* t);
	bool isOut();
};

	class Player : public Object {
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
