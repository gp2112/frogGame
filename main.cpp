#include "SDL2/SDL.h"
//#include "SDL2Image/SDL_image.h"
#include "stdio.h"
#include <cstring>
#include <iostream>
using namespace std;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Event *event;
} App;

typedef struct {
  SDL_Texture *texture;
  int x;
  int y;
  int hp;

} Player;

App app;

void setup(){
	SDL_Init(SDL_INIT_EVERYTHING);
	app.window = SDL_CreateWindow("title",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,600,400,SDL_WINDOW_SHOWN);
	app.render = SDL_CreateRenderer(app.window, -1, 0);

	SDL_SetRenderDrawColor(app.render, 0, 255, 0, 255);
	SDL_RenderClear(app.render);

	SDL_RenderPresent(app.render);

}


int cor=0;
void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.render, cor, 255, 0, 255);
	SDL_RenderClear(app.render);
}

void presentScene(void){
    
	SDL_RenderPresent(app.render);
}
void getInput(void){
	
	while (SDL_PollEvent(app.event))
	{
		switch (app.event->type)
		{
			case SDL_QUIT:
				exit(0);
				break;

            case SDL_MOUSEBUTTONDOWN:
            break;

            case SDL_MOUSEBUTTONUP:
            break;
            
            case SDL_KEYDOWN:
                cout<<app.event->key.keysym.sym<<"\n";
            break;
			default:
				break;
		}
    }
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(app.render, filename);

	return texture;
}
void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(app.render, texture, NULL, &dest);
}
Player player;
int main(int argc, char *argv[]) {
    memset(&app,0,sizeof(App));
    setup();
    
	memset(&player, 0, sizeof(Player));
	player.x = 100;
	player.y = 100;
	player.texture = loadTexture("gfx/player.png");
    while(true){
      prepareScene();
      getInput();
		blit(player.texture, player.x, player.y);
      presentScene();
      SDL_Delay(16);
    }
	return 0;
}
