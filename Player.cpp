//---------------------------------------------------------------------------------------------------------------------
// Player.cpp
//
// Class for Player
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Player.hpp"
#include "Treasure.hpp"

Player::Player(PlayerColor player_color) : nr_found_treasures_{0}, player_color_(player_color) {}

const std::vector<PlayerColor> Player::player_colors_ = 
    {PlayerColor::RED, PlayerColor::YELLOW, PlayerColor::GREEN, PlayerColor::BLUE};

std::vector<Treasure*>& Player::getCoveredStackRef() 
{
  return covered_stack_;
}

size_t Player::getNrFoundTreasures()
{
  return nr_found_treasures_;
}

PlayerColor Player::getPlayerColor()
{
  return player_color_;
}

std::string Player::getPlayerColorAsString()
{
  switch (player_color_)
  {
    case PlayerColor::RED:
      return "Red";
    case PlayerColor::YELLOW:
      return "Yellow";
    case PlayerColor::GREEN:
      return "Green";
    case PlayerColor::BLUE:
      return "Blue";
  }
}

size_t Player::getCol()
{
  return col_;
}

size_t Player::getRow()
{
  return row_;
}

void Player::setNrFoundTreasures(size_t nr_found_treasures)
{
  nr_found_treasures_ = nr_found_treasures;
}

void Player::setPlayerColor(PlayerColor player_color)
{
  player_color_ = player_color;
}

void Player::setCol(size_t col)
{
  col_ = col;
}

void Player::setRow(size_t row)
{
  row_ = row;
}
