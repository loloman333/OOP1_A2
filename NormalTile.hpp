//----------------------------------------------------------------------------------------------------------------------
// NormalTile.hpp
//
// Represents a normal Tile with no further functionality than the super class Tile
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//----------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_NORMALTILE_HPP
#define A2_NORMALTILE_HPP


#include "Tile.hpp"

class NormalTile : public Tile
{
  private:

  public:

    //------------------------------------------------------------------------------------------------------------------
    ///
    /// constructor with a given tile type and rotation
    ///
    /// @param type the tiletype for the new tile
    /// @param rotation the rotation in which the tile has been rotated
    //
    NormalTile(TileType type, Rotation rotation);

    //------------------------------------------------------------------------------------------------------------------
    ///
    /// constructor with a given tile type
    ///
    /// @param type the tiletype for the new tile
    //
    NormalTile(TileType type);

    //------------------------------------------------------------------------------------------------------------------
    ///
    /// generates the string vector of the tile
    ///
    /// @returns the string vector of the tile
    //
    std::vector<std::string> getTileString();

};

#endif //A2_NORMALTILE_HPP