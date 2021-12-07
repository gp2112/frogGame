#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"
#include "SDL_image.h"
#include "constants.hpp"
#include "Object.hpp"

class Graphics {

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	//SDL_Texture* textures[TEXTURE_N];


public:
	Graphics();
	void renderObj(Object* obj);
	void show(); 
	SDL_Renderer* getRenderer();
};

#endif