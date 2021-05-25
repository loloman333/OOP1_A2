//---------------------------------------------------------------------------------------------------------------------
// CommandMaster.cpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Game.hpp"
#include "CommandMaster.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "TreasureTile.hpp"
#include "StartTile.hpp"
#include "Treasure.hpp"

#include <iostream>
#include <algorithm>

void CommandMaster::reset()
{
  inserted_ = false;
  show_treasure_ = false;
  show_gamefield_ = true;
}

bool CommandMaster::handleCommand()
{
  std::string command;
  std::getline(std::cin, command);
  std::vector<std::string> tokens = tokenize(command);
  return executeCommand(tokens);
}

std::vector<std::string> CommandMaster::tokenize(std::string input)
{
  std::vector<std::string> tokens;
  std::string token = "";
  for(size_t i = 0; i < input.size(); i++)
  {
    if(input[i] == ' ')
    {
      if(token.size() > 0)
      {
        tokens.push_back(token);
        token = "";
      }
    }
    else
    {
      token.push_back(input[i]);
    }
  }
  if(token.size() > 0)
  {
    tokens.push_back(token);
  }
  return tokens;
}

bool CommandMaster::executeCommand(std::vector<std::string>& tokens)
{
  std::string command = "";
  if(tokens.size() > 0)
  {
    command = tokens[0];
  }

  if(std::cin.eof() || command == "quit" || command == "exit")
  {
    game_.quitGame();
    return true;
  }
  else if(command == "showtreasure" || command == "st")
  {
    showTreasure(tokens);
  }
  else if(command == "hidetreasure" || command == "ht")
  {
    hideTreasure(tokens);
  }
  else if(command == "showfreetile" || command == "sft")
  {
    showFreeTile(tokens);
  }
  else if(command == "rotate")
  {
    rotateFreeTile(tokens);
  }
  else if(command == "insert" || command == "i")
  {
    insert(tokens);
  }
  else if(command == "gamefield" || command == "g")
  {
    gameField(tokens);
  }
  else if(command == "finish" || command == "f")
  {
    return finish(tokens);
  }
  else if(std::find(PLAYER_MOVEMENT.begin(), PLAYER_MOVEMENT.end(), command) != PLAYER_MOVEMENT.end())
  {
    if(inserted_)
    {
      movePlayer(tokens);
    }
    else
    {
      moveNotAllowed(tokens);
    }
  }
  else if(command == "")
  {
    return false;
  }
  else
  {
    invalidCommand(command);
  }
  return false;
}

void CommandMaster::showTreasure(std::vector<std::string> tokens)
{
  if (tokens.size() > 1)
  {
    commandTakesNoArguments();
  }
  else
  {
    show_treasure_ = true;
    if(show_gamefield_)
    {
      game_.printGame();
    }
    else
    {
      printTreasure();
    }
  }
}


void CommandMaster::printTreasure()
{
  std::vector<Treasure*> covered_stack = game_.getCurrentPlayer()->getCoveredStackRef();
  if(covered_stack.empty())
  {
    std::cout << "All Treasures found, return to your startfield to win!" << std::endl;
  }
  else
  {
    Treasure *next_treasure = covered_stack.back();
    std::string treasure_name = next_treasure->getName();
    size_t treasure_id = next_treasure->getTreasureId();
    std::string id_string = "";

    if (treasure_id < 10)
    {
      id_string = "0";
    }
    id_string += std::to_string(treasure_id);

    std::cout << "Current Treasure: " << treasure_name << " Nr.: " << id_string << std::endl;
  }
}

void CommandMaster::hideTreasure(std::vector<std::string> tokens)
{
  if (tokens.size() == 1)
  {
    show_treasure_ = false;
    std::cout << UI_CLEAR;
    game_.printGame();
  }
  else
  {
    commandTakesNoArguments();
  }
}


void CommandMaster::showFreeTile(std::vector<std::string> tokens)
{
  if (tokens.size() == 1)
  {
    std::cout << "Free tile:" << std::endl;
    game_.getFreeTile()->print();
  }
  else if (tokens.size() > 1)
  {
    commandTakesNoArguments();
  }
}

void CommandMaster::rotateFreeTile(std::vector<std::string> tokens)
{
  if (!inserted_)
  {
    if (tokens.size() == 2)
    {
      std::string direction = tokens[1];
      if(direction == "l" || direction == "left")
      {
        game_.getFreeTile()->rotate(Direction::LEFT);
      }
      else if (direction == "r" || direction == "right")
      {
        game_.getFreeTile()->rotate(Direction::RIGHT);
      }
      else
      {
        invalidParameter(direction);
      }
    }
    else
    {
      wrongNumberArguments();
    }
  }
  else
  {
    commandNotAllowed(tokens);
  }
}

void CommandMaster::gameField(std::vector<std::string> tokens)
{
  if (tokens.size() > 2)
  {
    wrongNumberArguments();
  }
  else if (tokens.size() == 2)
  {
    if (tokens[1] == "on")
    {
      show_gamefield_ = true;
    }
    else if (tokens[1] == "off")
    {
      show_gamefield_ = false;
    }
    else{
      invalidParameter(tokens[1]);
    }
  }
  else
  {
    game_.printGame();
  }
}


bool CommandMaster::finish(std::vector<std::string> tokens)
{
  if (inserted_)
  {
    if (tokens.size() != 1)
    {
      commandTakesNoArguments();
      return false;
    }

    size_t player_row = game_.getCurrentPlayer()->getRow();
    size_t player_column = game_.getCurrentPlayer()->getCol();
    if (game_.getBoard()[player_row][player_column]->hasTreasure())
    {
      TreasureTile *tile = dynamic_cast<TreasureTile *>(game_.getBoard()[player_row][player_column]);
      if (currentPlayerNeedsTreasure(tile->getTreasure()))
      {
        currentPlayerCollectTreasure(tile->getTreasure());
      }
    }

    if (game_.isCorner(player_row, player_column))
    {
      StartTile *tile = dynamic_cast<StartTile *>(game_.getBoard()[player_row][player_column]);
      if (game_.getCurrentPlayer()->getPlayerColor() == tile->getPlayerColor())
      {
        if (game_.getCurrentPlayer()->getCoveredStackRef().empty())
        {
          std::string color = game_.getCurrentPlayer()->getPlayerColorAsString();
          std::transform(color.begin(), color.end(), color.begin(), ::toupper);

          std::cout << UI_WIN_1 << color << UI_WIN_2 << std::endl;
          game_.quitGame();
          return true;
        }
      }
    }

    show_treasure_ = false;
    game_.nextPlayer();
    return true;
  }
  else
  {
    commandNotAllowed(tokens);
    return false;
  }
}


bool CommandMaster::currentPlayerNeedsTreasure(Treasure* treasure)
{
  std::vector<Treasure*>& stack = game_.getCurrentPlayer()->getCoveredStackRef();
  if (stack.empty() || stack.back() != treasure)
  {
    return false;
  }
  return true;
}

void CommandMaster::currentPlayerCollectTreasure(Treasure* treasure)
{
  treasure->setFound(true);
  std::vector<Treasure*>& stack = game_.getCurrentPlayer()->getCoveredStackRef();
  stack.pop_back();
  game_.getCurrentPlayer()->incrementNrFoundTreasures();
}

void CommandMaster::insert(std::vector <std::string> tokens)
{
  if (tokens.size() == 3)
  {
    if(checkInsertParameter(tokens))
    {
      insertTile(tokens);
      inserted_ = true;
    }
  }
  else
  {
    wrongNumberArguments();
  }
}

bool CommandMaster::checkInsertParameter(std::vector <std::string> tokens)
{
  if (isValidInsertDirection(tokens[1]))
  {
    size_t row_col;
    try
    {
      row_col = std::stoi(tokens[2]);
    }
    catch (std::invalid_argument)
    {
      invalidParameter(tokens[2]);
      return false;
    }
    if (isInMoveableRowOrCol(row_col))
    {
      if (checkLastInsert(tokens))
      {
        return true;
      }
      else
      {
        commandNotAllowed(tokens);
      }
    }
    else
    {
      invalidParameter(tokens[2]);
    }
  }
  else
  {
    invalidParameter(tokens[1]);
  }

  return false;
}

bool CommandMaster::isValidInsertDirection(std::string direction)
{
  if (direction == "t" || direction == "top")
  {
    return true;
  }
  else if (direction == "l" || direction == "left")
  {
    return true;
  }
  else if (direction == "b" || direction == "bottom")
  {
    return true;
  }
  else if (direction == "r" || direction == "right")
  {
    return true;
  }
  return false;
}

bool CommandMaster::isInMoveableRowOrCol(size_t row_col)
{
  if (row_col < 1 || row_col > 7)
  {
    return false;
  }
  return ((row_col - 1) % 2 == 1);
}

bool CommandMaster::checkLastInsert(std::vector <std::string> tokens)
{
  if (tokens[1] == "t" || tokens[1] == "top")
  {
    return compareLastInsert("b", "bottom", tokens[2]);
  }
  else if (tokens[1] == "l" || tokens[1] == "left")
  {
    return compareLastInsert("r", "right", tokens[2]);
  }
  else if (tokens[1] == "b" || tokens[1] == "bottom")
  {
    return compareLastInsert("t", "top", tokens[2]);
  }
  else
  {
    return compareLastInsert("l", "left", tokens[2]);
  }
}

bool CommandMaster::compareLastInsert(std::string direction, std::string alias, std::string row_col)
{
  if (last_insert_direction_ == direction || last_insert_direction_ == alias)
  {
    if (last_insert_row_col_ == row_col)
    {
      return false;
    }
  }
  return true;
}

void CommandMaster::insertTile(std::vector <std::string> tokens)
{
  if (tokens[1] == "t" || tokens[1] == "top")
  {
    insertColumn(tokens);
  }
  else if (tokens[1] == "l" || tokens[1] == "left")
  {
    insertRow(tokens);
  }
  else if (tokens[1] == "b" || tokens[1] == "bottom")
  {
    insertColumn(tokens);
  }
  else if (tokens[1] == "r" || tokens[1] == "right")
  {
    insertRow(tokens);
  }
  last_insert_row_col_ = tokens[2];
  last_insert_direction_ = tokens[1];
  game_.printGame();
}

void CommandMaster::insertRow(std::vector <std::string> tokens)
{
  size_t row = std::stoi(tokens[2]) - 1;
  Tile* temp_free_tile = game_.getFreeTile();
  std::vector<std::vector<Tile*>>& board = game_.getBoard();
  if (tokens[1] == "l" || tokens[1] == "left")
  {
    game_.setFreeTile(board[row][6]);
    for(size_t column = 6; column > 0; column--)
    {
      board[row][column] = board[row][column - 1];
      playersUpdateRowColumn(board[row][column]->getPlayers(), row, column);
    }
    board[row][0] = temp_free_tile;
    movePlayersToTile(game_.getFreeTile(), row, 0);
  }
  else
  {
    game_.setFreeTile(board[row][0]);
    for(size_t column = 0; column < 6; column++)
    {
      board[row][column] = board[row][column + 1];
      playersUpdateRowColumn(board[row][column]->getPlayers(), row, column);
    }
    board[row][BOARD_SIZE - 1] = temp_free_tile;
    movePlayersToTile(game_.getFreeTile(), row, BOARD_SIZE - 1);
  }
}

void CommandMaster::insertColumn(std::vector <std::string> tokens)
{
  size_t column = std::stoi(tokens[2]) - 1;
  Tile* temp_free_tile = game_.getFreeTile();
  std::vector<std::vector<Tile*>>& board = game_.getBoard();

  if (tokens[1] == "t" || tokens[1] == "top")
  {
    game_.setFreeTile(board[6][column]);
    for(size_t row = BOARD_SIZE - 1; row > 0; row--)
    {
      board[row][column] = board[row - 1][column];
      playersUpdateRowColumn(board[row][column]->getPlayers(), row, column);
    }
    board[0][column] = temp_free_tile;
    movePlayersToTile(game_.getFreeTile(), 0, column);
  }
  else
  {
    game_.setFreeTile(board[0][column]);
    for(size_t row = 0; row < BOARD_SIZE - 1; row++)
    {
      board[row][column] = board[row + 1][column];
      playersUpdateRowColumn(board[row][column]->getPlayers(), row, column);
    }
    board[BOARD_SIZE - 1][column] = temp_free_tile;
    movePlayersToTile(game_.getFreeTile(), BOARD_SIZE - 1, column);
  }
}

void CommandMaster::movePlayersToTile(Tile* from, size_t row, size_t column)
{
  for(Player* player : from->getPlayers())
  {
    game_.getBoard()[row][column]->addPlayer(player);
    player->setRowCol(row, column);
  }
}

void CommandMaster::playersUpdateRowColumn(std::vector<Player*> players, size_t row, size_t column)
{
  for(Player* player : players)
  {
    player->setRow(row);
    player->setCol(column);
  }
}

void CommandMaster::movePlayer(std::vector<std::string> tokens)
{
  if(checkMoveInput(tokens))
  {
    Direction direction = getDirection(tokens);
    if(!(direction == Direction::UNDEFINED))
    {
      size_t movement = getAmount(tokens);
      if(!(movement == 0))
      {
        int row_modifier = 0;
        int col_modifier = 0;
        getMovementModifier(direction, row_modifier, col_modifier);
        if(isMovePossible(direction, movement, row_modifier, col_modifier))
        {
          moveInDirection(game_.getCurrentPlayer(), movement, row_modifier, col_modifier);
          game_.printGameIfNecessary();
        }
        else
        {
          impossibleMove();
        }
      }
    }
  }
}

bool CommandMaster::checkMoveInput(std::vector<std::string> tokens)
{
  if(tokens[0] == "go")
  {
    if(tokens.size() > 1 && tokens.size() < 4)
    {
      return true;
    }
    else
    {
      wrongNumberArguments();
      return false;
    }
  }
  else if(tokens.size() == 1)
  {
    return true;
  }
  else
  {
    commandTakesNoArguments();
    return false;
  }
}

Direction CommandMaster::getDirection(std::vector<std::string> tokens)
{
  if(tokens[0] == "go")
  {
    if(tokens[1] == "up")
    {
      return Direction::TOP;
    }
    else if(tokens[1] == "left")
    {
      return Direction::LEFT;
    }
    else if(tokens[1] == "down")
    {
      return Direction::BOTTOM;
    }
    else if(tokens[1] == "right")
    {
      return Direction::RIGHT;
    }
  }
  else
  {
    for(size_t index = 0; index < PLAYER_MOVEMENT.size(); index++)
    {
      if(tokens[0] == PLAYER_MOVEMENT[index])
      {
        if(index < MOVE_TOP)
        {
          return Direction::TOP;
        }
        else if(index < MOVE_LEFT)
        {
          return Direction::LEFT;
        }
        else if(index < MOVE_BOTTOM)
        {
          return Direction::BOTTOM;
        }
        else if(index < MOVE_RIGHT)
        {
          return Direction::RIGHT;
        }
      }
    }
  }
  invalidParameter(tokens[1]);
  return Direction::UNDEFINED;
}

int CommandMaster::getAmount(std::vector<std::string> tokens)
{
  int amount = 0;
  if(tokens[0] == "go" && tokens.size() == 3)
  {
    try
    {
      amount = std::stoi(tokens[2]);
      return amount;
    }
    catch(std::invalid_argument)
    {
      invalidParameter(tokens[2]);
      return 0;
    }

  }
  else
  {
    return 1;
  }
}

void CommandMaster::getMovementModifier(Direction direction, int &row_modifier, int &col_modifier)
{
  row_modifier = (static_cast<size_t>(direction) + 1) % 2;
  col_modifier = static_cast<size_t>(direction) % 2;
  if(direction == Direction::LEFT)
  {
    col_modifier = col_modifier * -1;
  }
  if(direction == Direction::TOP)
  {
    row_modifier = row_modifier * -1;
  }
}

bool CommandMaster::isMovePossible(Direction direction, size_t movement, int &row_modifier, int &col_modifier)
{
  Direction opposite_direction = getOppositeDirection(direction);

  for(size_t index = 0; index <= movement; index++)
  {
    size_t row = game_.getCurrentPlayer()->getRow() + (index * row_modifier);
    size_t col = game_.getCurrentPlayer()->getCol() + (index * col_modifier);
    if(row >= 7 || col >= 7)
    {
      return false;
    }
    Tile* current_tile = game_.getBoard()[row][col];
    bool wall_in_front = current_tile->isWallInDirection(direction);
    bool wall_behind = current_tile->isWallInDirection(opposite_direction);
    if(index == 0 && wall_in_front)
    {
      return false;
    }
    else if(index != 0 && index != movement && (wall_behind || wall_in_front))
    {
      return false;
    }
    else if(index == movement && wall_behind)
    {
      return false;
    }
  }
  return true;
}

void CommandMaster::moveInDirection(Player* player, size_t movement, int &row_modifier, int &col_modifier)
{
  std::string player_color = player->getPlayerColorAsString();
  size_t old_row = player->getRow();
  size_t old_col = player->getCol();
  size_t new_row = player->getRow() + (movement * row_modifier);
  size_t new_col = player->getCol() + (movement * col_modifier);
  player->setRow(new_row);
  player->setCol(new_col);
  game_.getBoard()[old_row][old_col]->removePlayer(player_color);
  game_.getBoard()[new_row][new_col]->addPlayer(player);
}

Direction CommandMaster::getOppositeDirection(Direction direction)
{
  switch (direction)
  {
    case Direction::TOP:
      return Direction::BOTTOM;
    case Direction::LEFT:
      return Direction::RIGHT;
    case Direction::BOTTOM:
      return Direction::TOP;
    case Direction::RIGHT:
      return Direction::LEFT;
    default:
      return Direction::UNDEFINED;
  }
}

void CommandMaster::invalidCommand(std::string command)
{
  std::cout << COMMAND_INVALID << "\"" << command << "\"" << std::endl;
}

void CommandMaster::invalidParameter(std::string parameter)
{
  std::cout << COMMAND_INVALID_PARAMETER << "\"" << parameter << "\"" << std::endl;
}

void CommandMaster::wrongNumberArguments()
{
  std::cout << COMMAND_WRONG_NUMBER_ARGUMENTS << std::endl;
}

void CommandMaster::commandTakesNoArguments()
{
  std::cout << COMMAND_TAKES_NO_ARGUMENTS << std::endl;
}

void CommandMaster::commandNotAllowed(std::vector<std::string> tokens)
{
  std::string invalid_command = "";
  for (size_t index = 0; index < tokens.size(); index++)
  {
    invalid_command += (tokens[index] + " ");
  }
  std::cout << "\"" << invalid_command.substr(0, invalid_command.length() - 1)
            << "\"" << COMMAND_NOT_ALLOWED << std::endl;
}

void CommandMaster::impossibleMove()
{
  std::cout << IMPOSSIBLE_MOVE << std::endl;
}

void CommandMaster::moveNotAllowed(std::vector<std::string> tokens)
{
  std::vector<std::string> edited_tokens = tokens;
  if(tokens[0] == PLAYER_MOVEMENT[1])
  {
    edited_tokens[0] = "arrow up";
  }
  else if(tokens[0] == PLAYER_MOVEMENT[3])
  {
    edited_tokens[0] = "arrow left";
  }
  else if(tokens[0] == PLAYER_MOVEMENT[5])
  {
    edited_tokens[0] = "arrow down";
  }
  else if(tokens[0] == PLAYER_MOVEMENT[7])
  {
    edited_tokens[0] = "arrow right";
  }
  commandNotAllowed(edited_tokens);
}

bool CommandMaster::getShowGamefield()
{
  return show_gamefield_;
}

bool CommandMaster::getShowTreasure()
{
  return show_treasure_;
}

