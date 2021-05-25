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
const size_t ARGUMENT_COUNT = 1;
const size_t EXIT_WRONG_ARGUMENTS = 2;

int main(int argc, [[maybe_unused]] char* argv[])
{
  if(argc == ARGUMENT_COUNT)
  {
    Game& game = Game::instance();
    return game.run();
  }
  else
  {
    std::cout << WRONG_ARGUMENTS << std::endl;
    return EXIT_WRONG_ARGUMENTS;
  }
}