//---------------------------------------------------------------------------------------------------------------------
// PrintMaster.hpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_PRINTMASTER_HPP
#define A2_PRINTMASTER_HPP

#include <vector>
#include <string>

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

const std::string COMMAND_INVALID = "Invalid command: ";
const std::string COMMAND_INVALID_PARAMETER = "Invalid parameter: ";
const std::string COMMAND_WRONG_NUMBER_ARGUMENTS = "Wrong number of arguments!";
const std::string COMMAND_TAKES_NO_ARGUMENTS = "This command does not take any arguments!";
const std::string COMMAND_NOT_ALLOWED = " is currently not allowed";
const std::string IMPOSSIBLE_MOVE = "Impossible move!";
const std::string ALL_TREASURES_FOUND = "All Treasures found, return to your startfield to win!";
const std::string CURRENT_TREASURE = "Current Treasure: ";
const std::string TREASURE_NUMBER = " Nr.: ";
const std::string FREE_TILE = "Free tile:";
const std::string INVALID_POSITION = "Invalid Position!";
const std::string ROPE_CANT_MOVE = "You can't move because you are tied up";

const std::string UI_LADDER_PROMPT = "You can go in all directions, with your next move. Choose wisely!";
const std::string UI_WHERE_WALL = "Where do you want to build the wall? ";
const std::string UI_WALL_EXISTS = "Wall already exists!";
const std::string UI_WALL_BUILT = "Wall built";
const std::string ROPE_NO_PLAYER = "No player to tie up here.";
const std::string ROPE_TIED_1 = "Player ";
const std::string ROPE_TIED_2 = " tied up.";
const std::string UI_BOMB = "BOOOOOOOOOMMMMM!!!!";

const size_t UI_PLAYER_TITLE_OFFSET = 58;
const size_t UI_ARROW_OFFSET = 17;

class Game;
enum class Direction;

class PrintMaster
{

private:
  Game& game_;

  void printBoard();
  std::vector<std::string> generateUILines();
  void addPlayerTitlesToLine(std::string& line, size_t& player_index);
  void addTreasureCountersToLine(std::string& line, size_t& player_index);
  void addArrowBasesToLine(std::string& line);
  void addArrowTipsToLine(std::string& line, Direction direction);
  void printRightUI(bool print_arrow);
  void printTilesOfLine(std::vector<std::vector<std::string>>& tile_strings, size_t tile_line_index);
  void printLeftUI(size_t& row_index, size_t line_index, size_t& row_label_index, bool& print_arrow);

public:
  PrintMaster(Game& game);

  void printFreeTile();
  void printGameIfNecessary();
  void printTreasure();
  void resetUI();
  void printWin(std::string color);
  void printGame();
  
  // Items
  void tiedUpPlayer(std::string player);
  void noPlayerToTieUp();
  void ladderUsed();
  void whereWall();
  void wallExists();
  void wallBuilt();
  void ladderUsed();
  void noItem();
  void printBomb();

  // Error messages
  void invalidCommand(std::string command);
  void invalidParameter(std::string parameter);
  void wrongNumberArguments();
  void commandTakesNoArguments();
  void commandNotAllowed(std::vector<std::string> tokens);
  void commandNotAllowed(std::string command);
  void impossibleMove();
  void invalidInsertPosition();
};

#endif // A2_PRINTMASTER_HPP