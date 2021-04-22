//---------------------------------------------------------------------------------------------------------------------
// Game.cpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Game.hpp"


Game::Game() {}

Game& Game::instance()
{
  static Game instance_;
  return instance_;
}

void Game::run(){

  gameStart(); //Nagy
  distributeTreasures(); //Grill
  fillBoard(); //Killer

  // While something
  while (true) 
  {
    print();
    playRound();
  }
}