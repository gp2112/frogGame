//#undef main

#include <iostream>
#include "Game.hpp"

using namespace std;

int main(int argc, char **argv) {

    // Cria jogo
    Game* game = new Game();

    // Inicializa
    game->play();
    
    
    
    return 0;
}