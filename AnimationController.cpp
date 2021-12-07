#include "AnimationController.hpp"

#include <SDL2/SDL.h>


AnimationController::AnimationController(int w0, int h0, int rate0, int n0) {
	index = 0;
	w = w0;
	h = h0;
	rate = rate0;
	n = n0;
}

void AnimationController::setAnimation(int offset0, int n1) {
	offset = offset;
	index = offset;
	n = n1;
}

void AnimationController::updateFrame() {
	Uint32 seconds = SDL_GetTicks()/1000;
	index = offset + ((seconds/rate)%n)*width;
}