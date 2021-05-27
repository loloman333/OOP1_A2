//---------------------------------------------------------------------------------------------------------------------
// CommandMaster.hpp
//
// The commandmaster handles all commands entered in the command line
// and calls the corresponding functions in other classes
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_COMMANDMASTER_HPP
#define A2_COMMANDMASTER_HPP

#include <string>
#include <vector>

const std::vector<std::string> PLAYER_MOVEMENT{"w", "\x1b[A", "a", "\x1b[D", "s", "\x1b[B", "d", "\x1b[C", "go"};

const size_t MOVE_TOP = 2;
const size_t MOVE_LEFT = 4;
const size_t MOVE_BOTTOM = 6;
const size_t MOVE_RIGHT = 8;
const size_t ARROW_UP_INDEX = 1;
const size_t ARROW_LEFT_INDEX = 3;
const size_t ARROW_DOWN_INDEX = 5;
const size_t ARROW_RIGHT_INDEX = 7;
const size_t MOVEMENT_DIRECTION_INDEX = 1;
const size_t COMMAND_INDEX = 0;

class Player;
class Tile;
class Treasure;
class Game;
class Item;
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
  bool stringToSizeT(std::string token, size_t& number);

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
  void currentPlayerCollectItem(Item* item);
  bool checkCollectTreasure(Treasure*& treasure_to_collect);
  bool checkCollectItem(Item*& item_to_collect);
  bool checkWin();

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
  void notUsed();

  // Move

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// moves the current player to the location given in the command tokens
  ///
  /// @param tokens the command tokens that have to be handled
  //
  void movePlayer(std::vector<std::string> tokens);

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// checks if the command tokens of the movement command are corrent
  ///
  /// @param tokens the command tokens that have to be handled
  /// @returns true if the input is correct else false
  //
  bool checkMoveInput(std::vector<std::string> tokens);

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// gets the direction to be moved from the command tokens
  ///
  /// @param tokens the command tokens that have to be handled
  /// @returns the direction the move has to go
  //
  Direction getDirection(std::vector<std::string> tokens);

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// checks if the command tokens of the movement command are corrent
  ///
  /// @param tokens the command tokens that have to be handled
  /// @returns the amount to be moved
  //
  size_t getAmount(std::vector<std::string> tokens);

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// calculates the modifier on the row and column that have to be added to move in specified direction
  /// row_modifier = 0 if the movement is in column direction only 
  /// else it is 1 or -1 depending on moving forwards or backwards
  /// col_modifier = 0 if the movement is in row direction only
  /// else it is 1 or -1 depending on moving forwards or backwards
  ///
  /// @param direction the direction in which the move happens
  /// @param row_modifier the modifier that is added to the movement to walk in specified direction
  /// @param col_modifier the modifier that is added to the movement to walk in specified direction
  //
  void getMovementModifier(Direction direction, int &row_modifier, int &col_modifier);

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// checks if the movement is possible or if walls or the edge are in the way
  ///
  /// @param direction the direction to be moved in
  /// @param movement the amount of tiles to be moved
  /// @param row_modifier the modifier to be used when moving in row direction
  /// @param col_modifier the modifier to be used when moving in column direction
  /// @returns true if the move is possible else false
  //
  bool isMovePossible(Direction direction, size_t movement, int &row_modifier, int &col_modifier);

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// moves the player in the specified direction
  ///
  /// @param player the player to be moved
  /// @param movement the amount of tiles to be moved
  /// @param row_modifier the modifier to be used when moving in row direction
  /// @param col_modifier the modifier to be used when moving in column direction
  //
  void moveInDirection(Player* player, size_t movement, int &row_modifier, int &col_modifier);

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// gets the direction opposite of the one given
  ///
  /// @param direction the direction from which the opposite is needed
  /// @returns the direction in the opposite direction
  //
  Direction getOppositeDirection(Direction direction);

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// prints the error Message that the move is not allowed
  ///
  /// @param command the command string that is not allowed and needs to be printed
  //
  void moveNotAllowed(std::string command);

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// uses the item of the current player, if the player has none an error is printed
  //
  void useItem();

public:

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// constructor with a reference to the game
  ///
  /// @param game the game on which the CommandMaster operstes
  //
  CommandMaster(Game& game);

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// tokenize takes the string input and splits it up into tokens for the other commands to operate with
  ///
  /// @param input the string of the whole command
  //
  std::vector<std::string> tokenize(std::string input);

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// handles all command  the user inputs on his turn and returns if the game should end or not
  ///
  /// @returns true if the game should be ended else false
  //
  bool handleCommand();

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// resets the round so round specific flags are on their standard values
  //
  void reset();

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// Getter for the showTreasure variable
  ///
  /// @returns the value of showTreasure
  //
  bool getShowTreasure();

  //---------------------------------------------------------------------------------------------------------------------
  ///
  /// Getter for the showGamefield variable
  ///
  /// @returns the value of showGamefield
  //
  bool getShowGamefield();
};

#endif // A2_COMMANDMASTER_HPP
