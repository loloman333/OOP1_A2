//---------------------------------------------------------------------------------------------------------------------
// main.cpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Game.hpp"
#include <iostream>

int main(int argc)
{
  if(argc == 1)
  {
    Game& game = Game::instance();
    game.run();
  }
  else
  {
    std::cout << "Wrong arguments!" << std::endl;
    return 2;
  }
}