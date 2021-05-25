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

#include <vector>
#include <string>

class Tile;
class Player;
class Treasure;
class CommandMaster;
enum class PlayerColor;
enum class TileType;
enum class Direction;

const size_t BOARD_SIZE = 7;
const size_t MOVE_TOP = 2;
const size_t MOVE_LEFT = 4;
const size_t MOVE_BOTTOM = 6;
const size_t MOVE_RIGHT = 8;

const std::string UI_WELCOME = "Welcome to the Wild OOP Labyrinth!!!";
const std::string UI_PLAYER_COUNT = "Player Count (2-4): ";
const std::string UI_WRONG_COUNT = "Wrong Input only a Number from 2 to 4 is allowed!";
const std::string UI_WIN_1 = "The Player ";
const std::string UI_WIN_2 = " has won the game!";
const std::string UI_CLEAR = "\x1b[2J";

const std::string UI_ARROW_RIGHT = "-->";
const std::string UI_ARROW_LEFT = "<--";
const std::string UI_DOWN_ARROWS = "V                 V                 V";
const std::string UI_UP_ARROWS = "Ʌ                 Ʌ                 Ʌ";
const std::string UI_ARROW_BASES = "|                 |                 |";
const std::string UI_COLUMN_LABELS = "        1        2        3        4        5        6        7    ";
const std::string UI_TREASURE_COUNTER = "Treasure: ";
const std::string UI_PLAYER_BASE = "Player ";

const size_t UI_PLAYER_TITLE_OFFSET = 58;
const size_t UI_ARROW_OFFSET = 17;

class Game
{
private:
  std::vector<std::vector<Tile*>> board_;
  Tile* free_tile_;
  std::vector<Treasure*> treasures_;
  std::vector<Player*> players_;
  size_t current_player_index_ = 0;
  bool quit_ = false;
  CommandMaster* command_master_;

  Game();
  Game(const Game&);
  Game& operator=(const Game&);

  bool gameIsRunning();

  // Preparations
  void gameStart();
  void addPlayer(PlayerColor color);
  void distributeTreasures();
  void fillBoard();
  void fillStaticTiles(size_t& treasure_index);
  void fillVariableTiles(size_t& treasure_index);
  void addNewNormalTilesToVector(std::vector<Tile*>& vector, TileType type, size_t count);
  void addNewTreasureTilesToVector(std::vector<Tile*>& vector, TileType type, size_t count, size_t& treasure_index);
  bool isInMoveableLine(size_t row_index, size_t col_index);
  void fillTreasures();

  // Free memory
  void deleteTreasures();
  void deleteFreeTile();
  void deleteBoard();
  void deletePlayers();

  // Print board
  void printBoard();
  std::vector<std::string> generateUILines();
  void addPlayerTitlesToLine(std::string& line, size_t& player_index);
  void addTreasureCountersToLine(std::string& line, size_t& player_index);
  void addArrowBasesToLine(std::string& line);
  void addArrowTipsToLine(std::string& line, Direction direction);
  void printRightUI(bool print_arrow);
  void printTilesOfLine(std::vector<std::vector<std::string>>& tile_strings, size_t tile_line_index);
  void printLeftUI(size_t& row_index, size_t line_index, size_t& row_label_index, bool& print_arrow);

  void playRound();


public:
  void nextPlayer();
  bool isCorner(size_t row_index, size_t col_index);
  std::vector<std::vector<Tile*>>& getBoard();
  Player* getCurrentPlayer();
  Tile* getFreeTile();
  void setFreeTile(Tile* tile);
  void printGame();
  void printGameIfNecessary();
  void quitGame();
  static Game& instance();
  ~Game();

  int run();
};

#endif // A2_GAME_HPP
