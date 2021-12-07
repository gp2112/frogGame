#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "AnimationController.hpp"


class Graphics {

private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *textures[TEXTURE_N];


public:
	Graphics();
	void renderPlayerTexture();
	void renderObjTexture();

};

#endif