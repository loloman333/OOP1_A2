//---------------------------------------------------------------------------------------------------------------------
// Tile.hpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_TILE_HPP
#define A2_TILE_HPP

#include <cstdlib>
#include <string>
#include <vector>
#include "Player.hpp"

//Enums
enum class TileType {T, L, I, O, U, X};
enum class Rotation{DEG0 = 0, DEG90 = 1, DEG180 = 2, DEG270 = 3};

class Tile
{
  private:
    TileType type_;
    Rotation rotation_;
    std::vector<Player*> players_;

  public:
    Tile(TileType type, Rotation rotation);
    virtual ~Tile() = default;

    TileType getType();
    Rotation getRotation();
    std::vector<Player*> getPlayers();

    void setRotation(Rotation r);

    std::vector<std::string> virtual getTileString() = 0;
    size_t getRotationValue();
    std::string getTileTypeString();
};

#endif //A2_TILE_HPP