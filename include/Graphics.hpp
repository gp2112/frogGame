#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifndef __linux__
	#include "SDL.h"
	#include "SDL_image.h"
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#endif


#include "constants.hpp"
#include "Object.hpp"

class Graphics {

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* textures[TEXTURE_N];


public:
	Graphics();
	void renderObj(Object* obj);
	void show(); 
	SDL_Renderer* getRenderer();
	SDL_Texture* getTexture(int id);
};

#endif