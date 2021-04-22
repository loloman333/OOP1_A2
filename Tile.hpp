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
#include <iostream>

const std::string WALL = "█";

//Enums
enum class TileType {T, L, I, O, U, X};
enum class Rotation{DEG0 = 0, DEG90 = 1, DEG180 = 2, DEG270 = 3};
enum class Direction{TOP = 0, LEFT = 1, BOTTOM = 2, RIGHT = 3};

class Tile
{
  private:
    TileType type_;
    Rotation rotation_;
    std::vector<Player*> players_;

    void fillWalls(std::vector<Direction>, std::vector<std::string>& tile);
    void generateTile(Rotation rotation, std::vector<Direction> directions, std::vector<std::string>& tile);
    void addPlayersToTile(std::vector<std::string>& tileVector);
    Direction calcDirection(Direction dir, Rotation rot);

  public:
    Tile() = default;
    Tile(TileType type, Rotation rotation);
    virtual ~Tile() = default;

    TileType getType();
    Rotation getRotation();
    std::vector<Player*> getPlayers();

    void setRotation(Rotation r);
    void setType(TileType type);

    std::vector<std::string> virtual getTileString() = 0;
    std::vector<std::string> getRawTileString();
    size_t getRotationValue();
    std::string getTileTypeString();
    void addPlayer(Player* player);
};

#endif //A2_TILE_HPP