#include "AnimationController.hpp"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>


AnimationController::AnimationController(int w0, int h0, int rate0, int n0) {
	index = 0;
	offset = 0;
	w = w0;
	h = h0;
	rate = rate0;
	n = n0;
}

void AnimationController::setAnimation(int offset0, int n1) {
	offset = offset0;
	index = offset;
	n = n1;
}

void AnimationController::updateFrame() {
	Uint32 ticks = SDL_GetTicks();
	index = offset + ((ticks / rate) % n) ;
}

int AnimationController::getW() {
	return w;
}
int AnimationController::getH() {
	return h;
}
int AnimationController::getIndex() {
	return index;
}