#include "../include/Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create and run the game
    Game game;
    game.initialize();
    game.run();

    return 0;
}
