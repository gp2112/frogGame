#include <cmath>
#include <iostream>
#include "Graphics.hpp"

Graphics::Graphics() {
	
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
	//blues
	// 96, 192, 214
	// 102, 162,209
	// 169, 211, 209
	// 135, 151,255
	// red
	// 190, 36, 94

	//grey
	// 23,23,23
	SDL_RenderClear(renderer);

	textures[TX_BG] = IMG_LoadTexture(renderer, "img/bg.png");
	textures[TX_CLOUDS_D] = IMG_LoadTexture(renderer, "img/clouds_dark.png");
	textures[TX_CLOUDS_L] = IMG_LoadTexture(renderer, "img/clouds_light.png");
	textures[TX_FROG] = IMG_LoadTexture(renderer, "img/frog.png");
	textures[TX_FX_GREEN] = IMG_LoadTexture(renderer, "img/fx_green.png");
	textures[TX_FX_YELLOW] = IMG_LoadTexture(renderer, "img/fx_yellow.png");
	textures[TX_HEARTS] = IMG_LoadTexture(renderer, "img/hearts.png");
	textures[TX_HEARTS_ORANGE] = IMG_LoadTexture(renderer, "img/hearts_orange.png");
	textures[TX_NUMBERS] = IMG_LoadTexture(renderer, "img/numbers.png");
	textures[TX_NUMBERS_ORANGE] = IMG_LoadTexture(renderer, "img/numbers_orange.png");
	textures[TX_PERSON_CUIA] = IMG_LoadTexture(renderer, "img/personage_cuia.png");
	textures[TX_PERSON_NOCAP] = IMG_LoadTexture(renderer, "img/player_nocap.png");
	textures[TX_PERSON_SPRITE] = IMG_LoadTexture(renderer, "img/player_spritesheetCuia.png");
	textures[TX_BG2] = IMG_LoadTexture(renderer, "img/bg2.png");

	//AnimationController* animationController = new AnimationController(32,40,10,4);

}

SDL_Texture *Graphics::getTexture(int id) {
	if (id >= TEXTURE_N || id < 0)
		return NULL;
	return textures[id];
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