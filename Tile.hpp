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
#include <iostream>

const std::string WALL = "█";
const std::size_t TILE_HEIGHT = 5;
const std::size_t TILE_WIDTH = 9;
const std::size_t DIRECTION_AMOUNT = 4;
const std::size_t TOP_ROW = 0;
const std::size_t BOTTOM_ROW = 4;
const std::size_t LEFT_COLUMN = 1;
const std::size_t RIGHT_COLUMN = 7;

const size_t TREASURE_TILE_ROW = 2;
const size_t PLAYER_TILE_ROW = 2;
const size_t INDEX_WITHOUT_WALL = 3;
const size_t INDEX_WITH_WALL = 7;

//Enums
enum class TileType {T, L, I, O, U, X};
enum class Rotation{DEG0 = 0, DEG90 = 1, DEG180 = 2, DEG270 = 3};
enum class Direction{TOP = 0, LEFT = 1, BOTTOM = 2, RIGHT = 3};

class Player;

class Tile
{
  private:
    TileType type_;
    Rotation rotation_;
    std::vector<Player*> players_;
    std::vector<Direction> walls_;

    void fillTileString(std::vector<std::string>& tile);
    void generateTile(Rotation rotation,std::vector<Direction> directions);
    void addPlayersToTile(std::vector<std::string>& tileVector);
    Direction calcDirection(Direction dir, Rotation rot);
    bool isCorner(size_t row, size_t col);
    std::vector<bool> calcWalls();
    void setWalls();
    

  public:
    Tile() = default;
    Tile(TileType type);
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
    void removePlayer(std::string player_color);

    bool isWallInDirection(Direction direction);
    void print();
    void rotate(Direction dir);
};

#endif //A2_TILE_HPP