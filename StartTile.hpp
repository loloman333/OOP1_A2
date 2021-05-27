//---------------------------------------------------------------------------------------------------------------------
// StartTile.hpp
//
// The Start Tile class represents a tile in the corner of the board where players can start the game.
// It is a subclass of "Tile" and implements all necessary functions
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_START_TILE_HPP
#define A2_START_TILE_HPP

#include "Tile.hpp"

const size_t PLAYER_TILE_ROW = 2;

enum class PlayerColor;

class StartTile : public Tile
{
  private:
    PlayerColor player_color_;

  public:

    ///-----------------------------------------------------------------------------------------------------------------
    /// Constructor for the StartTile class
    /// Takes a playercolor and sets Type and Rotation based on that
    ///
    /// @param player_color The color of the player that should start the game here
    ///
    StartTile(PlayerColor player_color);

    ///-----------------------------------------------------------------------------------------------------------------  
    /// Getter for player_color_;
    ///
    /// @return The color of the player starting on this tile
    ///
    PlayerColor getPlayerColor();

    ///-----------------------------------------------------------------------------------------------------------------  
    /// Implemented getTileString function of "Tile" superclass
    /// Returns a vector of string for each line of the tile to print it.
    ///
    /// @return All the lines of the tile as vector of strings
    ///
    std::vector<std::string> getTileString();
};

#endif //A2_START_TILE_HPP
