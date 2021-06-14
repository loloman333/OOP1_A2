//----------------------------------------------------------------------------------------------------------------------
// AIMaster.cpp
//
// TODO
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//----------------------------------------------------------------------------------------------------------------------
//

#include "AIMaster.hpp"

#include "Game.hpp"
#include "Player.hpp"

AIMaster::AIMaster(Game& game) : game_{game} {};

bool AIMaster::isConnected(Player* current_player, size_t to_row, size_t to_column)
{
  return true;
}