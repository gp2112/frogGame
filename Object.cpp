#include "Object.hpp"

#include <cmath>


/*
Representa qualquer objeto do jogo

*/

Object::Object(int x0, int y0, int h0, int w0, bool wa, double sx, double sy, AnimationController* anim, SDL_Texture* tx) {
	dirX = 0; 
	dirY = 0;
	x = x0;
	y = y0;
	h = h0;
	w = w0;
	wall = wa;
	speed_x = sx;
	speed_y = sy;
	animationController = anim;
	texture = tx;
}

Player::Player(int x0, int y0, int h0, int w0, bool wa, double sx, double sy, AnimationController* anim, SDL_Texture* tx) :
Object(x0,y0,h0,w0,wa,sx,sy,anim,tx){
	hp = PLAYER_MAX_HP;
	is_hit = false;
}

int Player::getHp() {
	return hp;
}
void Player::setHp(int hp0) {
	hp = hp0;
}
bool Player::getDamage() {
	hp--;
	return (hp != 0);
}
void Object::move() {
	x += speed_x*dirX;
	y += speed_y*dirY;

	speed_x += ac_x;
	speed_y += ac_y;
}
void Object::setDir(int _x, int _y) {
	dirX = _x;
	dirY = _y;
}


// retorna distancia do objeto para outro
double Object::dist(Object *obj) {
	return sqrt(pow(x-obj->getX(), 2) +  pow(y-obj->getY(), 2))
	- (sqrt(h*h +  w*w) + sqrt(obj->getH()*obj->getH() + obj->getW()*obj->getW()))/2;
}

int Object::getDirX() {
	return dirX;
}

int Object::getDirY() {
	return dirY;
}

void Object::update() {
	animationController->updateFrame();
}

int Object::getH() {
	return h;
}
SDL_Texture* Object::getTexture() {
	return texture;
}

int Object::getW() {
	return w;
}
int Object::getX() {
	return x;
}
int Object::getY() {
	return y;
}

void Object::setAceleration(double _x, double _y) {
	ac_x = _x;
	ac_y = _y;
}

double Object::getSpeedY() {
	return y;
}
double Object::getSpeedX() {
	return x;
}
void Object::setSpeed(double _x, double _y) {
	speed_x = _x;
	speed_y = _y;
}
void Object::setPosition(int _x, int _y) {
	x = _x;
	y = _y;
}
void Object::setSize(int _w, int _h) {
	w = _w;
	h = _h;
}
bool Object::isOut() {
	return (x < -w || x > WIDTH+w || y < -h || y > HEIGHT+h);
}
AnimationController* Object::getAnimationController() {
	return animationController;
}