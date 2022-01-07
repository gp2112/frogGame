#include "Game.hpp"
#include <iostream>



Game::Game() {
	graphics = new Graphics();
	points = 0;

    // Cria thread para a entrada de inputs do teclado
    t_input = std::thread(&Game::getInput, this);
    mixer = new Mixer(&quit);
}

// Inicializa pontuação
void Game::setupPoints() {
    for (int i = 0; i < 4; i++) {
        AnimationController* pointAnim = new AnimationController(16, 16, 100, 10);
        SDL_Texture* texture = graphics->getTexture(TX_NUMBERS);
        Object* pointObj = new Object(100-30*i, 10, 32, 32, false, 0, 0, pointAnim, texture);
        pointsViewer.push_back(pointObj);
    }
    showPoints();
}

// Mostra pontuação
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

// Cria um objeto caindo
void Game::createFrog() {
    AnimationController* frogAnim = new AnimationController(20, 20, 100, 4);
    if (rand() % 10 > 5) // define aleatoriamente se vai ser um tijolo
        frogAnim->setIndex(1);
    SDL_Texture* texture = graphics->getTexture(TX_FROG);
    Object* frog = new Object(rand()%(WIDTH-80)+40, -40, 40, 40, false, 0, 0, frogAnim, texture);
    frog->setDir(0, 1);
    frog->setAceleration(0, GRAVITY);
    frogs.push_back(frog);
}

// Cria um visual fx
void Game::createFx(int off,int n) {

    AnimationController* anim = new AnimationController(32, 32, 100, 5);
    SDL_Texture* texture = graphics->getTexture(TX_FX_YELLOW);
    anim->setIndex(0);
    anim->setAnimation(off, n);
    Object* fx = new Object(player->getX()-16, player->getY()-20, 100, 100, false, 0, 0, anim, texture);
    fxObjs.push_back(fx);
}

// Mostra efeitos visuais
void Game::showFxs() {

    std::list<Object*>::iterator k;
    std::list<Object*>::iterator aux;
    AnimationController* anim;
    Object* fx; 
    Uint32 ticks = SDL_GetTicks();
    for (k = fxObjs.begin(); k != fxObjs.end(); k++) {
        fx = *k;
        anim = fx->getAnimationController();
        int frameId = anim->getIndex();
        if (ticks %2 == 0)
            anim->setIndex(frameId + 1);

        // posição do fx é na cabeça do player
        fx->setPosition(player->getX() - 16,fx->getY());

        if (frameId >= anim->getN()) {
            // ao chegar no fim da animação
            // dela objeto (visual fx)
            aux = k;
            delete* aux;
            k = fxObjs.erase(k);
            if (k == fxObjs.end())
                break;

        }else
        // renderiza fx
        graphics->renderObj(fx);
    }
}

void Game::removeFrog(std::list<Object*>::iterator k) {
    
}

// Lógica dos sapos/ objetos caindo
void Game::moveFrogs() {
    std::list<Object*>::iterator k;
    std::list<Object*>::iterator aux;
    Object* fallingObj;
    AnimationController* anim;
    for (k = frogs.begin(); k != frogs.end(); k++) {
        // move objeto
        fallingObj = *k;
        fallingObj->move();
        anim = fallingObj->getAnimationController();
        // renderiza objeto
        graphics->renderObj(fallingObj);

        // caso seja um sapo
        if (anim->getIndex() != 1) { // index = 1 (é um tijolo)

            // sapo colidindo com o player (coleta o sapo)
            if (player->dist(fallingObj) < -20) {
                mixer->play(SAMPLE_FROG);
                points++; // aumenta pontuação
                createFx(0,5); // efeito amarelo


                // deleta objeto
                aux = k;
                delete* aux;
                k = frogs.erase(k);
                if (k == frogs.end())
                    break;
            }

            // sapo caiu da tela (player perde vida)
            else if (fallingObj->getY() > 0 && fallingObj->isOut()) {
                gameOver = (!player->getDamage());
                // deleta objeto fora da tela
                aux = k;
                delete* aux;
                k = frogs.erase(k);
                if (k == frogs.end())
                    break;
            }
        }
        // se for um tijolo
        else {
            // tijolo colidindo com o player (perde vida)
            if (player->dist(fallingObj) < -20) {
                mixer->play(SAMPLE_COL);
                gameOver = (!player->getDamage());
                createFx(6,10); // efeito vermelho de dano


                // deleta objeto
                aux = k;
                delete* aux;
                k = frogs.erase(k);
                if (k == frogs.end())
                    break;
            }
            // tijolo caiu da tela
            else if (fallingObj->getY() > 0 && fallingObj->isOut()) {
                // deleta objeto fora da tela
                aux = k;
                delete* aux;
                k = frogs.erase(k);
                if (k == frogs.end())
                    break;
            }
        }
    }
}

// Inicializa corações
void Game::setupHearts() {
    for (int i = 0; i < PLAYER_MAX_HP; i++) {
        AnimationController* anim = new AnimationController(16, 16, 100, 7);
        SDL_Texture* texture = graphics->getTexture(TX_HEARTS);
        anim->setIndex(0);
        Object* heart = new Object(WIDTH-i*32-42, 10, 32, 32, false, 0, 0, anim, texture);
        hearts.push_front(heart);
    }
}

// Mostra objetos dos corações
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

// Reinicia o jogo
void Game::restart() {
    gameOver = false;
    points = 0;
    frogs.clear();
    pointsViewer.clear();
    hearts.clear();
    fxObjs.clear();
    setupScenary();
    setupPlayer();
    setupPoints();
    setupHearts();
}

// Inicializa jogador
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
            if (down) {
                pause=false;
                restart();
            }
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

// Inicializa cenário
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


// Tela de derrota que mostra a pontuação no centro
void Game::endScreen() {

    pause = true;
    AnimationController* anim = new AnimationController(200, 300, 100, 7);
    SDL_Texture* texture = graphics->getTexture(TX_BG2);
    anim->setIndex(0);
    front = new Object(0, 0, 600, 400, false, 0, 0, anim, texture);



    std::list<Object *>::iterator k;
    Object *pointView;
    int size = 56;
    int i = 0;

    // coloca objetos da pontuação no centro da tela
    for (k = pointsViewer.begin(); k != pointsViewer.end(); k++) {
        pointView = *k;
        anim = pointView->getAnimationController();
        pointView->setPosition(WIDTH / 2 + size -i * size, HEIGHT / 2- size);
        pointView->setSize(size, size);
        i++;
    }

}


// Inicializa o jogo
void Game::play() {

    
    Uint32 seconds;

    // inicializa objeto do jogador (protagonista)
    setupPlayer();

    // inicializa objetos que mostram os numeros da pontuação
    setupPoints();

    // inicializa objetos do cenário (background/foreground)
    setupScenary();

    // inicializa objetos dos corações que mostram a vida do player
    setupHearts();

    int i = 0;

    // game loop
    while (!quit) {

        // tela final - jogo pausado
        if (pause) {
            graphics->renderObj(back);
            graphics->renderObj(front);
            showPoints();
            graphics->show();
            continue;
        }

        // se perdeu, inicializa a tela final
        if (gameOver) {
            endScreen();
        }


        // contador
        i += 1;

        // cria um objeto caindo no topo da tela
        // (pode ser um sapo ou tijolo)
        if (i == 50) {
            i = 0;
            createFrog();
        }

        // renderiza a imagem de background
        graphics->renderObj(back);

        // movimenta/atualiza sprite do jogador
        player->move();
        player->update();

        // movimenta/atualiza e renderiza sapos e objetos caindo
        moveFrogs();

        // renderiza jogador
        graphics->renderObj(player);

        // renderiza visual fxs
        showFxs();

        // renderiza a imagem de foreground
        graphics->renderObj(front);

        // atualiza/renderiza pontuação 
        showPoints();

        // atualiza/renderiza vida do jogador
        showHearts();

        // exibe tooos os objetos gráficos na tela
        graphics->show();

        SDL_Delay(16);
    }
}