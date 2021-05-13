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
const std::vector<std::string> PLAYER_MOVEMENT{"w", "\x1b[A", "a", "\x1b[D", "s", "\x1b[B", "d", "\x1b[C", "go"};

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

const std::string COMMAND_INVALID = "Invalid command: ";
const std::string COMMAND_INVALID_PARAMETER = "Invalid parameter: ";
const std::string COMMAND_WRONG_NUMBER_ARGUMENTS = "Wrong number of arguments!";
const std::string COMMAND_TAKES_NO_ARGUMENTS = "This command does not take any arguments!";

class Game
{
  private:

    std::vector<std::vector<Tile*>> board_;
    Tile* free_tile_;
    std::vector<Treasure*> treasures_;
    std::vector<Player*> players_;
    size_t currentPlayerIndex_ = 0;
    bool showGamefield_ = true;

    Game();
    Game(const Game&); 
    Game& operator = (const Game&);

    // Preparations
    void gameStart();
    void addPlayer(char color);
    void distributeTreasures();
    void fillBoard();
    void fillStaticTiles(size_t& treasure_index);
    void fillVariableTiles(size_t& treasure_index);
    void addNewNormalTilesToVector(std::vector<Tile*>& vector, TileType type, size_t count);
    void addNewTreasureTilesToVector(std::vector<Tile*>& vector, TileType type, size_t count, size_t& treasure_index);
    bool isCorner(size_t row_index, size_t col_index);
    void fillTreasures();

    // Free memory
    void deleteTreasures();
    void deleteFreeTile();
    void deleteBoard();
    void deletePlayers();

    // Commands
    std::vector<std::string> tokenize(std::string input);
    void executeCommand(std::vector<std::string>& tokens);
    void showTreasure(std::vector<std::string> tokens);
    void hideTreasure(std::vector<std::string> tokens);
    void showFreeTile(std::vector<std::string> tokens);
    void rotateFreeTile(std::vector<std::string> tokens);
    void gameField(std::vector<std::string> tokens);

    // Print board
    void print();
    void printBoard();
    void printBoardIfNecessary();
    std::vector<std::string> generateUILines();
    void addPlayerTitlesToLine(std::string& line, size_t& player_index);
    void addTreasureCountersToLine(std::string& line, size_t& player_index);
    void addArrowBasesToLine(std::string& line);
    void addArrowTipsToLine(std::string& line, Direction direction);

    void playRound();
    void nextPlayer();
    Player* getCurrentPlayer();

  public:
    static Game& instance();
    ~ Game();

    void run();
};

#endif //A2_GAME_HPP
