#include "Object.hpp"

Object::Object(int x0, int y0, int h0, int w0, bool wa, int sx, int sy, AnimationController* anim, SDL_Texture* tx) {
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
void Object::move() {
	x += speed_x*dirX;
	y += speed_y*dirY;
}
void Object::setDir(int _x, int _y) {
	dirX = _x;
	dirY = _y;
}
void Object::update() {
	move();
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

int Object::getSpeedY() {
	return y;
}int Object::getSpeedX() {
	return x;
}
void Object::setSpeed(int _x, int _y) {
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
	return false;
}
AnimationController* Object::getAnimationController() {
	return animationController;
}