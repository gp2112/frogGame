#include "Game.hpp"
#include <iostream>

#include <thread>

Game::Game() {
	graphics = new Graphics();
	points = 0;
    t_input = std::thread(&Game::getInput, this);
    
}

void Game::createFrog() {

    AnimationController* frogAnim = new AnimationController(20, 20, 100, 4);
    SDL_Surface* image = IMG_Load("frog.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics->getRenderer(), image);
    Object* frog = new Object(rand()%(WIDTH-40)+20, -40, 40, 40, false, 0, 0, frogAnim, texture);
    frog->setDir(0, 1);
    frog->setAceleration(0, GRAVITY);
    frogs.push_back(frog);
}

void Game::removeFrog(std::list<Object*>::iterator k) {
    
}

void Game::moveFrogs() {
    std::list<Object*>::iterator k, aux;
    Object* frog;
    for (k = frogs.begin(); k != frogs.end(); k++) {
        frog = *k;
        frog->move();
        graphics->renderObj(frog);
        if (player->dist(frog) < -20 || frog->getY() > 0 && frog->isOut()) {
            aux = k;
            k--;
            frogs.erase(aux);
            delete *aux;
        }
        if (player->dist(frog) < -20)
            points++;
    }
}

void Game::setupPlayer() {

    AnimationController* playerAnim = new AnimationController(32, 40, 100, 4);
    SDL_Surface* image = IMG_Load("player_spritesheetCuia.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics->getRenderer(), image);
    player = new Object(WIDTH/2-32, HEIGHT-80, 80, 64, false, PLAYER_SPD, 0, playerAnim ,texture);

}

void Game::keyPressed(SDL_Keycode key, bool down) {

    AnimationController *anim;

    switch (key) {

        case SDLK_a:
        case SDLK_LEFT:
            anim = player->getAnimationController();

            if (down) {
                player->setDir(-1, 0);
                anim->setAnimation(4, 4);
            }
            else {
                player->setDir(0, 0);
                anim->setAnimation(0, 4);
            }
        break;

        case SDLK_d:
        case SDLK_RIGHT:
            anim = player->getAnimationController();

            if (down) {
                player->setDir(1, 0);
                anim->setAnimation(4, 4);
            }
            else {
                player->setDir(0, 0);
                anim->setAnimation(0, 4);
            }
        break;
        case SDLK_SPACE:
            
        break;
        case SDLK_ESCAPE:
            if (down)
                pause=!pause;
        break;
        case SDLK_BACKSPACE:
            //restart();
        break;
    }
}

void Game::getInput() {
    while (!quit) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYUP:
                keyPressed(event.key.keysym.sym, false);
            break;

            case SDL_KEYDOWN:

                keyPressed(event.key.keysym.sym, true);
                break;
        }
    }
}

void Game::play() {

    
    Uint32 seconds;
    setupPlayer();
    int i = 0;
    while (!quit) {
        if (pause)
            continue;
        i+=1;
        if (i >= 60) {
            i = 0;
            createFrog();
        }

        player->update();
        moveFrogs();

        graphics->renderObj(player);
        graphics->show();
        SDL_Delay(16);
    }
}