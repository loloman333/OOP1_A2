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

#include "Tile.hpp" // [FB] is the include here necessary? would a forward decleration suffice? When is in necessary to include header files?
#include "Random.hpp" // [FB] is the include here necessary? would a forward decleration suffice? Is anthing from the header file even used in this file?
#include <fstream>

const size_t BOARD_SIZE = 7;

const std::string UI_WELCOME = "Welcome to the Wild OOP Labyrinth!!!";
const std::string UI_PLAYER_COUNT = "Player Count (2-4): ";
const std::string UI_WRONG_COUNT = "Wrong Input only a Number from 2 to 4 is allowed!";

const std::string UI_ARROW_RIGHT = "-->";
const std::string UI_ARROW_LEFT = "<--";
const std::string UI_DOWN_ARROWS = "V                 V                 V";
const std::string UI_UP_ARROWS = "Ʌ                 Ʌ                 Ʌ";
const std::string UI_ARROW_BASES = "|                 |                 |";
const std::string UI_COLUMN_LABELS = "        1        2        3        4        5        6        7    ";
const std::string UI_TREASURE_COUNTER = "Treasure: ";
const std::string UI_PLAYER_RED = "Player Red(R)";
const std::string UI_PLAYER_YELLOW = "Player Yellow(Y)";
const std::string UI_PLAYER_GREEN = "Player Green(G)";
const std::string UI_PLAYER_BLUE = "Player Blue(B)";

class Game
{
  private:

    std::vector<std::vector<Tile*>> board_;
    Tile* free_tile_;
    std::vector<Treasure*> treasures_;
    std::vector<Player*> players_;
    size_t currentPlayerIndex_ = 0;

    Game();
    Game(const Game&); 
    Game& operator = (const Game&); // [FB] no need to put spaces in the method name

    bool isCorner(size_t row_index, size_t col_index);
    void fillTreasures();

    void deleteTreasures(); // [FB] missing deascriptions/headers
    void deleteFreeTile();
    void deleteBoard();
    void deletePlayers();

  public:
    static Game& instance();
    ~ Game();

    void run();
    void gameStart();
    void distributeTreasures();
    void fillBoard();
    void fillStaticTiles(size_t& treasure_index);
    void fillVariableTiles(size_t& treasure_index);
    void addNewNormalTilesToVector(std::vector<Tile*>& vector, TileType type, size_t count);
    void addNewTreasureTilesToVector(std::vector<Tile*>& vector, TileType type, size_t count, size_t& treasure_index);
    void playRound();    

    // Print
    void print();
    void printBoard();
    std::vector<std::string> generateUILines();
    void addPlayerTitlesToLine(std::string& line, size_t& player_index);
    void addTreasureCountersToLine(std::string& line, size_t& player_index);
    void addArrowBasesToLine(std::string& line);
    void addArrowTipsToLine(std::string& line, Direction direction);

    void addPlayer(char color);
    void nextPlayer();
    Player* getCurrentPlayer(); // [FB] how can you use the player class when you never declared it in the current file?
};

#endif //A2_GAME_HPP
