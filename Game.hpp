//---------------------------------------------------------------------------------------------------------------------
// Game.hpp
//
// Class for Game
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_GAME_HPP
#define A2_GAME_HPP

#include "Tile.hpp"
#include "Random.hpp"
#include <fstream>

const size_t BOARD_SIZE = 7;
const std::string TREASURE_PATH = "Treasures.txt";

class Game
{
  private:

    std::vector<std::vector<Tile*>> board_;
    std::vector<Treasure*> treasures_;
    std::vector<Player*> players_;

    Game();
    Game(const Game&); 
    Game& operator = (const Game&); 

    bool isCorner(size_t row_index, size_t col_index);
    void fillTreasures();

  public:
    static Game& instance();
    ~ Game() = default;

    void run();
    void gameStart();
    void distributeTreasures();
    void fillBoard();
    void fillStaticTiles();
    void fillVariableTiles();
    void addNewTilesToVector(std::vector<Tile*>& vector, TileType type, size_t count);
    void print();
    void playRound();

    void addPlayer(Player* player);
};

#endif //A2_GAME_HPP
