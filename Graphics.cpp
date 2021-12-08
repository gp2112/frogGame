#include <cmath>
#include <iostream>
#include "Graphics.hpp"

Graphics::Graphics() {
	
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
	SDL_RenderClear(renderer);

	//AnimationController* animationController = new AnimationController(32,40,10,4);

}
void Graphics::renderObj(Object *obj) {
	AnimationController* objAnim = obj->getAnimationController();
	int w = objAnim->getW();
	int id = objAnim->getIndex();
	int h = objAnim->getH();
	SDL_Rect srcrect = {w*id, 0, w, h};
	SDL_Rect dstrect = {obj->getX(), obj->getY(), obj->getW(), obj->getH()};
	
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	if (obj->getDirX()==-1)
		flip = SDL_FLIP_HORIZONTAL;

	SDL_RenderCopyEx(renderer, obj->getTexture(), &srcrect, &dstrect, 0, NULL, flip);
}

void Graphics::show() {
	SDL_RenderPresent(renderer); 
	SDL_RenderClear(renderer);
}

SDL_Renderer* Graphics::getRenderer() {
	return renderer;
}