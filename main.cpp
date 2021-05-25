//---------------------------------------------------------------------------------------------------------------------
// main.cpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Game.hpp"
#include <iostream>
#include <string>

const std::string WRONG_ARGUMENTS = "Wrong arguments!";

int main(int argc)
{
  if(argc == 1)
  {
    Game& game = Game::instance();
    return game.run();
  }
  else
  {
    std::cout << WRONG_ARGUMENTS << std::endl;
    return 2;
  }
}