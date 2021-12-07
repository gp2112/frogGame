// Your First C++ Program
#undef main
#include <iostream>
#include "Game.hpp"
using namespace std;
int main(int argc, char** argv) {
    Game* game = new Game();
    game->play();
    std::cout << "Hello World!";
    return 0;
}