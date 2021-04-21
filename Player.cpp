//---------------------------------------------------------------------------------------------------------------------
// Player.cpp
//
// Class for Player
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Player.hpp"

Player::Player(char player_color) : nr_found_treasures_{0}, player_color_(player_color) {}

std::vector<Treasure*>& Player::getCoveredStackRef() 
{
  return covered_stack_;
}

size_t Player::getNrFoundTreasures()
{
  return nr_found_treasures_;
}

char Player::getPlayerColor()
{
  return player_color_;
}

void Player::setNrFoundTreasures(size_t nr_found_treasures)
{
  nr_found_treasures_ = nr_found_treasures;
}

void Player::setPlayerColor(char player_color)
{
  player_color_ = player_color;
}
