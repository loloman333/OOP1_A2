//---------------------------------------------------------------------------------------------------------------------
// StartTile.hpp
//
// Class for Start Tile
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_START_TILE_HPP
#define A2_START_TILE_HPP

#include "Tile.hpp"

class StartTile : public Tile
{
  private:
    char player_color_;

  public:
    StartTile(char player_color);

    char getPlayerColor();

    std::vector<std::string> getTileString();
};


#endif //A2_START_TILE_HPP
