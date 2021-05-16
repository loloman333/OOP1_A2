//---------------------------------------------------------------------------------------------------------------------
// main.cpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Game.hpp"

int main(int argc) // [FB] main looks good so far. you could avoid having an if else, if you checked for (args != 1) and then returned in the if
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