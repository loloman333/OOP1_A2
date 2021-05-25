//---------------------------------------------------------------------------------------------------------------------
// CommandMaster.hpp
//
// Class for CommandMaster
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_COMMANDMASTER_HPP
#define A2_COMMANDMASTER_HPP

#include <string>
#include <vector>

const std::vector<std::string> PLAYER_MOVEMENT{"w", "\x1b[A", "a", "\x1b[D", "s", "\x1b[B", "d", "\x1b[C", "go"};

const std::string COMMAND_INVALID = "Invalid command: ";
const std::string COMMAND_INVALID_PARAMETER = "Invalid parameter: ";
const std::string COMMAND_WRONG_NUMBER_ARGUMENTS = "Wrong number of arguments!";
const std::string COMMAND_TAKES_NO_ARGUMENTS = "This command does not take any arguments!";
const std::string COMMAND_NOT_ALLOWED = " is currently not allowed";
const std::string IMPOSSIBLE_MOVE = "Impossible move!";

class Player;
class Tile;
class Treasure;
class Game;
enum class Direction;

class CommandMaster
{

private:
  Game& game_;

  bool inserted_ = false;
  bool show_treasure_ = false;
  bool show_gamefield_ = true;

  std::string last_insert_direction_ = "";
  std::string last_insert_row_col_ = "";

  bool executeCommand(std::vector<std::string>& tokens);

  // Treasure
  void showTreasure(std::vector<std::string> tokens);
  void hideTreasure(std::vector<std::string> tokens);

  // Free Tile
  void showFreeTile(std::vector<std::string> tokens);
  void rotateFreeTile(std::vector<std::string> tokens);

  // GameField
  void gameField(std::vector<std::string> tokens);

  // Finish
  bool finish(std::vector<std::string> tokens);
  bool currentPlayerNeedsTreasure(Treasure* treasure);
  void currentPlayerCollectTreasure(Treasure* treasure);

  // Insert
  void insert(std::vector<std::string> tokens);
  void insertTile(std::vector<std::string> tokens);
  bool checkInsertParameter(std::vector<std::string> tokens);
  bool isInMoveableRowOrCol(size_t row_col);
  bool isValidInsertDirection(std::string direction);
  bool checkLastInsert(std::vector<std::string> tokens);
  bool compareLastInsert(std::string direction, std::string alias, std::string row_col);
  void insertRow(std::vector<std::string> tokens);
  void insertColumn(std::vector<std::string> tokens);
  void playersUpdateRowColumn(std::vector<Player*> players, size_t row, size_t column);
  void movePlayersToTile(Tile* from, size_t row, size_t column);

  // Move
  void movePlayer(std::vector<std::string> tokens);
  bool checkMoveInput(std::vector<std::string> tokens);
  Direction getDirection(std::vector<std::string> tokens);
  int getAmount(std::vector<std::string> tokens);
  void getMovementModifier(Direction direction, int &row_modifier, int &col_modifier);
  bool isMovePossible(Direction direction, size_t movement, int &row_movement, int &col_movement);
  void moveInDirection(Player* player, size_t movement, int &row_movement, int &col_movement);
  Direction getOppositeDirection(Direction direction);

  // Error messages
  void invalidCommand(std::string command);
  void invalidParameter(std::string parameter);
  void wrongNumberArguments();
  void commandTakesNoArguments();
  void commandNotAllowed(std::vector<std::string> tokens);
  void impossibleMove();
  void moveNotAllowed(std::vector<std::string> tokens);

public:

  CommandMaster(Game& game) : game_{game} {};
  void reset();
  void printTreasure();
  bool getShowGamefield();
  bool getShowTreasure();
  std::vector<std::string> tokenize(std::string input);
  bool handleCommand();

};

#endif // A2_COMMANDMASTER_HPP
