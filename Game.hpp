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

const std::string UI_LINE_1 = "Player Red(R)    |                 |                 |    Player Yellow(Y)";
const std::string UI_LINE_2 = "Treasure: X/6    V                 V                 V    Treasure: X6";
const std::string UI_LINE_3 = "        1        2        3        4        5        6        7    ";
const std::string UI_LINE_4 = "Player Green(G)  Ʌ                 Ʌ                 Ʌ    Player Blue(B)";
const std::string UI_LINE_5 = "Treasure: X/6    |                 |                 |    Treasure: X/6";
const std::string UI_ARROW_RIGHT = "-->";
const std::string UI_ARROW_LEFT = "<--";

class Game
{
  private:

    std::vector<std::vector<Tile*>> board_;
    Tile* free_tile_;
    std::vector<Treasure*> treasures_;
    std::vector<Player*> players_;

    Game();
    Game(const Game&); 
    Game& operator = (const Game&); 

    bool isCorner(size_t row_index, size_t col_index);
    void fillTreasures();

    void deleteTreasures();
    void deleteFreeTile();
    void deleteBoard();

  public:
    static Game& instance();
    ~ Game();

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
