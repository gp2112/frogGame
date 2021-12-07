#include "Game.hpp"
#include <iostream>
Game::Game() {
	graphics = new Graphics();
	points = 0;
	is_paused = false;
}

void Game::createFrog() {

    AnimationController* frogAnim = new AnimationController(20, 20, 100, 4);
    SDL_Surface* image = IMG_Load("frog.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics->getRenderer(), image);
    Object* frog = new Object(rand()%(WIDTH-40)+20, -40, 40, 40, false, 1, rand()%4+1, frogAnim, texture);
    frog->setDir(0, 1);
    frogs.push_back(frog);
}
void Game::setupPlayer() {

    AnimationController* playerAnim = new AnimationController(32, 40, 100, 4);
    SDL_Surface* image = IMG_Load("player_spritesheetCuia.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics->getRenderer(), image);
    player = new Object(WIDTH/2-32, HEIGHT-80, 80, 64, false, 1, 1,playerAnim ,texture);

    //player->setDir(1, 0);
}
void Game::play() {
    std::list<Object*>::iterator k;
    Uint32 seconds;
    setupPlayer();
    int i = 0;
    while (!quit)
    {
        i+=1;
        if (i >= 60) {
            i = 0;
            createFrog();
        }
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            break;
        }
        player->update();
        for (k = frogs.begin(); k != frogs.end(); k++) {
            Object* frog = *k;
            frog->move();
            graphics->renderObj(frog);
        }

        graphics->renderObj(player);
        graphics->show();
        SDL_Delay(16);
    }
}