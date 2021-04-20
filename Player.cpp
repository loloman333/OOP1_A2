//---------------------------------------------------------------------------------------------------------------------
// Player.cpp
//
// Class for Player
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Player.hpp"

Player::Player() : nr_found_treasures_{0} {}

std::vector<Treasure*>& Player::getCoveredStackRef() 
{
  return covered_stack_;
}

size_t Player::getNrFoundTreasures()
{
  return nr_found_treasures_;
}

void Player::setNrFoundTreasures(size_t nr_found_treasures)
{
  nr_found_treasures_ = nr_found_treasures;
}
