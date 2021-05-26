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

  void ladderUsed();

  // Error messages
  void invalidCommand(std::string command);
  void invalidParameter(std::string parameter);
  void wrongNumberArguments();
  void commandTakesNoArguments();
  void commandNotAllowed(std::vector<std::string> tokens);
  void commandNotAllowed(std::string command);
  void impossibleMove();
};

#endif // A2_PRINTMASTER_HPP