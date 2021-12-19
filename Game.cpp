#include "Game.hpp"
#include <iostream>


Game::Game() {
	graphics = new Graphics();
	points = 0;
    t_input = std::thread(&Game::getInput, this);
    mixer = new Mixer(&quit);
}
void Game::setupPoints() {
    for (int i = 0; i < 4; i++) {
        AnimationController* pointAnim = new AnimationController(16, 16, 100, 10);
        SDL_Texture* texture = graphics->getTexture(TX_NUMBERS);
        Object* pointObj = new Object(100-30*i, 10, 32, 32, false, 0, 0, pointAnim, texture);
        pointsViewer.push_back(pointObj);
    }
    showPoints();
}
void Game::showPoints() {

    std::list<Object*>::iterator k;
    Object* pointView;
    int p = points;
    AnimationController* anim;
    for (k = pointsViewer.begin(); k != pointsViewer.end(); k++) {
        pointView = *k;
        anim = pointView->getAnimationController();
        anim->setIndex(p%10);
        p /= 10;
        graphics->renderObj(pointView);
    }
}
void Game::createFrog() {
    AnimationController* frogAnim = new AnimationController(20, 20, 100, 4);
    if (rand() % 10 > 5)
        frogAnim->setIndex(1);
    SDL_Texture* texture = graphics->getTexture(TX_FROG);
    Object* frog = new Object(rand()%(WIDTH-80)+40, -40, 40, 40, false, 0, 0, frogAnim, texture);
    frog->setDir(0, 1);
    frog->setAceleration(0, GRAVITY);
    frogs.push_back(frog);
}
void Game::createFx(int off,int n) {

    AnimationController* anim = new AnimationController(32, 32, 100, 5);
    SDL_Texture* texture = graphics->getTexture(TX_FX_YELLOW);
    anim->setIndex(0);
    anim->setAnimation(off, n);
    Object* fx = new Object(player->getX()-16, player->getY()-20, 100, 100, false, 0, 0, anim, texture);
    fxObjs.push_back(fx);
}
void Game::showFxs() {

    std::list<Object*>::iterator k;
    std::list<Object*>::iterator aux;
    AnimationController* anim;
    Object* fx; 
    Uint32 ticks = SDL_GetTicks();
    for (k = fxObjs.begin(); k != fxObjs.end(); k++) {
        fx = *k;
        //fx->update();
        anim = fx->getAnimationController();
        int frameId = anim->getIndex();
        if (ticks %2 == 0)
            anim->setIndex(frameId + 1);
        fx->setPosition(player->getX() - 16,fx->getY());
        if (frameId >= anim->getN()) {
            aux = k;
            delete* aux;
            k = fxObjs.erase(k);
            if (k == fxObjs.end())
                break;

        }else
        graphics->renderObj(fx);
    }
}
void Game::removeFrog(std::list<Object*>::iterator k) {
    
}

void Game::moveFrogs() {
    std::list<Object*>::iterator k;
    std::list<Object*>::iterator aux;
    Object* fallingObj;
    AnimationController* anim;
    for (k = frogs.begin(); k != frogs.end(); k++) {
        fallingObj = *k;
        fallingObj->move();
        anim = fallingObj->getAnimationController();
        graphics->renderObj(fallingObj);

        // is a frog
        if (anim->getIndex() != 1) {
            if (player->dist(fallingObj) < -20) {
                mixer->play(SAMPLE_FROG);
                points++;
                createFx(0,5);
                aux = k;
                delete* aux;
                k = frogs.erase(k);
                if (k == frogs.end())
                    break;
            }
            else if (fallingObj->getY() > 0 && fallingObj->isOut()) {
                gameOver = (!player->getDamage());

                aux = k;
                delete* aux;
                k = frogs.erase(k);
                if (k == frogs.end())
                    break;
            }
        }
        // is not a frog
        else {
            if (player->dist(fallingObj) < -20) {
                mixer->play(SAMPLE_COL);
                gameOver = (!player->getDamage());
                createFx(6,10);
                aux = k;
                delete* aux;
                k = frogs.erase(k);
                if (k == frogs.end())
                    break;
            }
            else if (fallingObj->getY() > 0 && fallingObj->isOut()) {
                aux = k;
                delete* aux;
                k = frogs.erase(k);
                if (k == frogs.end())
                    break;
            }
        }
    }
}
void Game::setupHearts() {
    for (int i = 0; i < PLAYER_MAX_HP; i++) {
        AnimationController* anim = new AnimationController(16, 16, 100, 7);
        SDL_Texture* texture = graphics->getTexture(TX_HEARTS);
        anim->setIndex(0);
        Object* heart = new Object(WIDTH-i*32-42, 10, 32, 32, false, 0, 0, anim, texture);
        hearts.push_front(heart);
    }
}
void Game::showHearts() {
    std::list<Object*>::iterator k;
    Object* heart;
    AnimationController* anim;
    int hp = player->getHp();
    for (k = hearts.begin(); k != hearts.end(); k++) {
        heart = *k;
        if(hp<=0){
            anim = heart->getAnimationController();
            anim->setIndex(1);
        }
        graphics->renderObj(heart);
        hp--;
    }
}
void Game::restart() {
    gameOver = false;
    points = 0;
    frogs.clear();
    pointsViewer.clear();
    hearts.clear();
    fxObjs.clear();
    setupPlayer();
    setupPoints();
    setupHearts();
}
void Game::setupPlayer() {

    AnimationController* playerAnim = new AnimationController(32, 40, 100, 4);
    SDL_Texture* texture = graphics->getTexture(TX_PERSON_SPRITE);
    player = new Player(WIDTH/2-32, HEIGHT-90, 80, 64, false, PLAYER_SPD, 0, playerAnim ,texture);


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
        while (SDL_PollEvent(&event)) {
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
}
void Game::setupScenary() {
    AnimationController* anim = new AnimationController(200, 300, 100, 7);
    SDL_Texture* texture = graphics->getTexture(TX_CLOUDS_L);
    anim->setIndex(0);
     front = new Object(0, 0, 600, 400, false, 0, 0, anim, texture);

      anim = new AnimationController(200, 300, 100, 7);
      texture = graphics->getTexture(TX_BG);
     anim->setIndex(0);
     back = new Object(0, 0, 600, 400, false, 0, 0, anim, texture);
}

void Game::play() {

    
    Uint32 seconds;
    setupPlayer();
    setupPoints();
    setupScenary();
    setupHearts();
    int i = 0;
    while (!quit) {
        if (pause)
            continue;
        if (gameOver)
            restart();
        i += 1;
        if (i == 50) {
            i = 0;
            createFrog();
        }
        graphics->renderObj(back);
        player->move();
        player->update();
        moveFrogs();
        graphics->renderObj(player);
        showFxs();
        graphics->renderObj(front);
        showPoints();
        showHearts();
        graphics->show();

        SDL_Delay(16);
    }
}