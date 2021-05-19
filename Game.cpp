//---------------------------------------------------------------------------------------------------------------------
// Game.cpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Game.hpp"
#include "StartTile.hpp"
#include "TreasureTile.hpp"
#include "NormalTile.hpp"
#include "Treasure.hpp"
#include "Random.hpp"
#include "Player.hpp"
#include "Tile.hpp"

#include <algorithm>

Game::Game() {}

Game::~Game()
{
  deleteFreeTile();
  deleteBoard();
  deleteTreasures();
  deletePlayers();
}

Game& Game::instance()
{
  static Game instance_;
  return instance_;
}

int Game::run()
{
  try
  {
    fillTreasures();

    gameStart();
    fillBoard();
    distributeTreasures();

    while (!quit_)
    {
      printGame();
      playRound();
    }
  } catch (std::bad_alloc)
  {
    return 1;
  }
  return 0;
}

void Game::gameStart()
{
  std::cout << UI_WELCOME << std::endl;

  std::string input;
  std::vector<std::string> input_vector;
  size_t player_count = 0;
  while (player_count == 0)
  {
    std::cout << UI_PLAYER_COUNT;
    std::getline(std::cin, input);
    input_vector = tokenize(input);
    if(input_vector.size() == 1)
    {
      if(input_vector[0] == "2")
      {
        player_count = 2;
      }
      else if(input_vector[0] == "3")
      {
        player_count = 3;
      }
      else if(input_vector[0] == "4")
      {
        player_count = 4;
      }
      else
      {
        std::cout << UI_WRONG_COUNT << std::endl;
      }
    }
    else
    {
      std::cout << UI_WRONG_COUNT << std::endl;
    }
  }

  for(size_t index = 0; index < player_count; index++)
  {
    addPlayer(Player::player_colors_[index]);
  }
}

void Game::playRound()
{
  inserted_ = false;
  Player* player = getCurrentPlayer();
  std::string current_output = player->getPlayerColorAsString();
  std::transform(current_output.begin(), current_output.end(), current_output.begin(), ::toupper);
  current_output += " > ";

  bool stop = false;
  while(!stop)
  {
    std::cout << current_output;
    std::string command;
    std::getline(std::cin, command);
    std::vector<std::string> tokens = tokenize(command);
    stop = executeCommand(tokens);
  }
}

bool Game::executeCommand(std::vector<std::string>& tokens)
{
  std::string command = "";
  if(tokens.size() > 0)
  {
    command = tokens[0];
  }

  if(std::cin.eof() || command == "quit" || command == "exit")
  {
    quit_ = true;
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
  else
  {
    invalidCommand(command);
  }
  return false;
}

bool Game::finish(std::vector<std::string> tokens)
{
  if (tokens.size() != 1)
  {
    commandTakesNoArguments();
    return false;
  }

  size_t player_row = getCurrentPlayer()->getRow();
  size_t player_column = getCurrentPlayer()->getCol();
  if (board_[player_row][player_column]->hasTreasure())
  {
    TreasureTile* tile = dynamic_cast<TreasureTile*>(board_[player_row][player_column]);
    if (currentPlayerNeedsTreasure(tile->getTreasure()))
    {
      currentPlayerCollectTreasure(tile->getTreasure());
    }
  }

  if (isCorner(player_row, player_column))
  {
    StartTile* tile = dynamic_cast<StartTile*>(board_[player_row][player_column]);
    if (getCurrentPlayer()->getPlayerColor() == tile->getPlayerColor())
    {
      if (getCurrentPlayer()->getCoveredStackRef().empty())
      {
        std::string color = getCurrentPlayer()->getPlayerColorAsString();
        std::transform(color.begin(), color.end(), color.begin(), ::toupper);

        std::cout << UI_WIN_1 << color << UI_WIN_2 << std::endl;
        quit_ = true;
        return true;
      }
    }
  }

  std::cout << UI_CLEAR;
  nextPlayer();
  return true;
}

bool Game::currentPlayerNeedsTreasure(Treasure* treasure)
{
  std::vector<Treasure*>& stack = getCurrentPlayer()->getCoveredStackRef();
  if (stack.empty() || stack.back() != treasure)
  {
    return false;
  }
  return true;
}

void Game::currentPlayerCollectTreasure(Treasure* treasure)
{
  treasure->setFound(true);
  std::vector<Treasure*>& stack = getCurrentPlayer()->getCoveredStackRef();
  stack.pop_back();
  getCurrentPlayer()->incrementNrFoundTreasures();
}

void Game::insert(std::vector <std::string> tokens)
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

bool Game::checkInsertParameter(std::vector <std::string> tokens)
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

bool Game::isValidInsertDirection(std::string direction)
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

bool Game::isInMoveableRowOrCol(size_t row_col)
{
  if (row_col < 1 || row_col > 7)
  {
    return false;
  }
  return ((row_col - 1) % 2 == 1);
}

bool Game::checkLastInsert(std::vector <std::string> tokens)
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

bool Game::compareLastInsert(std::string direction, std::string alias, std::string row_col)
{
  if (last_insert_direction == direction || last_insert_direction == alias)
  {
    if (last_insert_row_col == row_col)
    {
      return false;
    }
  }
  return true;
}

void Game::insertTile(std::vector <std::string> tokens)
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
  last_insert_row_col = tokens[2];
  last_insert_direction = tokens[1];
  printGame();
}

void Game::insertRow(std::vector <std::string> tokens)
{
  size_t row = std::stoi(tokens[2]) - 1;
  Tile* temp_free_tile = free_tile_;
  if (tokens[1] == "l" || tokens[1] == "left")
  {
    free_tile_ = board_[row][6];
    for(size_t column = 6; column > 0; column--)
    {
      board_[row][column] = board_[row][column - 1];
      playersUpdateRowColumn(board_[row][column]->getPlayers(), row, column);
    }
    board_[row][0] = temp_free_tile;
    movePlayersToTile(free_tile_, row, 0);
  }
  else
  {
    free_tile_ = board_[row][0];
    for(size_t column = 0; column < 6; column++)
    {
      board_[row][column] = board_[row][column + 1];
      playersUpdateRowColumn(board_[row][column]->getPlayers(), row, column);
    }
    board_[row][BOARD_SIZE - 1] = temp_free_tile;
    movePlayersToTile(free_tile_, row, BOARD_SIZE - 1);
  }
}

void Game::insertColumn(std::vector <std::string> tokens)
{
  size_t column = std::stoi(tokens[2]) - 1;
  Tile* temp_free_tile = free_tile_;
  if (tokens[1] == "t" || tokens[1] == "top")
  {
    free_tile_ = board_[6][column];
    for(size_t row = BOARD_SIZE - 1; row > 0; row--)
    {
      board_[row][column] = board_[row - 1][column];
      playersUpdateRowColumn(board_[row][column]->getPlayers(), row, column);
    }
    board_[0][column] = temp_free_tile;
    movePlayersToTile(free_tile_, 0, column);
  }
  else
  {
    free_tile_ = board_[0][column];
    for(size_t row = 0; row < BOARD_SIZE - 1; row++)
    {
      board_[row][column] = board_[row + 1][column];
      playersUpdateRowColumn(board_[row][column]->getPlayers(), row, column);
    }
    board_[BOARD_SIZE - 1][column] = temp_free_tile;
    movePlayersToTile(free_tile_, BOARD_SIZE - 1, column);
  }
}

void Game::movePlayersToTile(Tile* from, size_t row, size_t column)
{
  for(Player* player : from->getPlayers())
  {
    board_[row][column]->addPlayer(player);
    player->setRowCol(row, column);
  }
}

void Game::playersUpdateRowColumn(std::vector<Player*> players, size_t row, size_t column)
{
  for(Player* player : players)
  {
    player->setRow(row);
    player->setCol(column);
  }
}

void Game::gameField(std::vector<std::string> tokens)
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
    printGame();
  }
}

void Game::rotateFreeTile(std::vector<std::string> tokens)
{
  if (tokens.size() == 2)
  {
    std::string direction = tokens[1];
    if(direction == "l" || direction == "left")
    {
      free_tile_->rotate(Direction::LEFT);
    }
    else if (direction == "r" || direction == "right")
    {
      free_tile_->rotate(Direction::RIGHT);
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

void Game::showFreeTile(std::vector<std::string> tokens)
{
  if (tokens.size() == 1)
  {
    std::cout << "Free tile:" << std::endl;
    free_tile_->print();
  }
  else if (tokens.size() > 1)
  {
    commandTakesNoArguments();
  }
}

void Game::showTreasure(std::vector<std::string> tokens)
{
  if (tokens.size() > 1)
  {
    commandTakesNoArguments();
  }
  else
  {
    std::vector<Treasure*> covered_stack = getCurrentPlayer()->getCoveredStackRef();
    if(covered_stack.empty())
    {
      std::cout << "All Treasures found, return to your startfield to win!" << std::endl;
    }
    else
    {
      Treasure* next_treasure = covered_stack.back();
      std::string treasure_name = next_treasure->getName();
      size_t treasure_id = next_treasure->getTreasureId();
      std::string id_string= "";

      if (treasure_id < 10)
      {
        id_string = "0";
      }
      id_string += std::to_string(treasure_id);

      printGameIfNecessary();
      std::cout << "Current Treasure: " << treasure_name << " Nr.: " << id_string << std::endl;
    }
  }
}

void Game::hideTreasure(std::vector<std::string> tokens)
{
  if (tokens.size() == 1)
  {
    std::cout << UI_CLEAR;
    printGame();
  }
  else
  {
    commandTakesNoArguments();
  }
}


void Game::movePlayer(std::vector<std::string> tokens)
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
          moveInDirection(getCurrentPlayer(), movement, row_modifier, col_modifier);
          printGameIfNecessary();
        }
        else
        {
          impossibleMove();
        }
      }
    }
  }
}

bool Game::checkMoveInput(std::vector<std::string> tokens)
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

Direction Game::getDirection(std::vector<std::string> tokens)
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

int Game::getAmount(std::vector<std::string> tokens)
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

void Game::getMovementModifier(Direction direction, int &row_modifier, int &col_modifier)
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

bool Game::isMovePossible(Direction direction, size_t movement, int &row_modifier, int &col_modifier)
{
  Direction opposite_direction = getOppositeDirection(direction);
  
  for(size_t index = 0; index <= movement; index++)
  {
    size_t row = players_[current_player_index_]->getRow() + (index * row_modifier);
    size_t col = players_[current_player_index_]->getCol() + (index * col_modifier);
    if(row >= 7 || col >= 7)
    {
      return false;
    }
    Tile* current_tile = board_[row][col];
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

void Game::moveInDirection(Player* player, size_t movement, int &row_modifier, int &col_modifier)
{
  std::string player_color = player->getPlayerColorAsString();
  size_t old_row = player->getRow();
  size_t old_col = player->getCol();
  size_t new_row = player->getRow() + (movement * row_modifier);
  size_t new_col = player->getCol() + (movement * col_modifier);
  player->setRow(new_row);
  player->setCol(new_col);
  board_[old_row][old_col]->removePlayer(player_color);
  board_[new_row][new_col]->addPlayer(player);
}

Direction Game::getOppositeDirection(Direction direction)
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

void Game::printGameIfNecessary()
{
  if(show_gamefield_)
  {
    printGame();
  }
}

std::vector<std::string> Game::tokenize(std::string input)
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

void Game::fillBoard()
{
  size_t treasure_index = 0;
  fillStaticTiles(treasure_index);
  fillVariableTiles(treasure_index);
}

void Game::fillStaticTiles(size_t& treasure_index)
{
  size_t player_index = 0;

  for (size_t row_index = 0; row_index < BOARD_SIZE; row_index++)
  {
    board_.push_back(std::vector<Tile*>{});

    for (size_t col_index = 0; col_index < BOARD_SIZE; col_index++)
    {
      if (isInMoveableLine(row_index, col_index))
      {
        board_[row_index].push_back(nullptr);
      }
      else
      {
        if (isCorner(row_index, col_index))
        {
          Tile* tile = new StartTile{Player::player_colors_[player_index]};

          board_[row_index].push_back(tile);

          if (player_index < players_.size())
          {
            tile->addPlayer(players_[player_index]);
            players_[player_index]->setCol(col_index);
            players_[player_index]->setRow(row_index);
          }

          player_index++;
        }
        else
        {
          TreasureTile* treasure_tile = new TreasureTile(treasures_[treasure_index]);

          board_[row_index].push_back(treasure_tile);
          treasure_index++;
        }
      }
    }
  }
}

void Game::fillVariableTiles(size_t& treasure_index)
{
  std::vector<Tile*> tiles;
  addNewNormalTilesToVector(tiles, TileType::L, 11);
  addNewNormalTilesToVector(tiles, TileType::I, 11);
  addNewTreasureTilesToVector(tiles, TileType::T, 12, treasure_index);

  for (size_t row_index = 0; row_index < board_.size(); row_index++)
  {
    for (size_t col_index = 0; col_index < board_[row_index].size(); col_index++)
    {
      if (board_[row_index][col_index] == nullptr)
      {
        size_t random_index = Oop::Random::getInstance().getRandomCard(tiles.size()) - 1;
        board_[row_index][col_index] = tiles[random_index];

        size_t random_rotation = Oop::Random::getInstance().getRandomOrientation();
        board_[row_index][col_index]->setRotation((Rotation)random_rotation);

        tiles.erase(tiles.begin() + random_index);
      }
    }
  }
  free_tile_ = tiles[0];
}

void Game::addNewNormalTilesToVector(std::vector<Tile*>& vector, TileType type, size_t count)
{
  for (size_t i = 0; i < count; i++)
  {
    NormalTile* normal_tile = new NormalTile(type);
    vector.push_back(normal_tile);
  }
}

void Game::addNewTreasureTilesToVector(std::vector<Tile*>& vector, TileType type, size_t count, size_t& treasure_index)
{
  for (size_t i = 0; i < count; i++)
  {
    Tile* tile = new TreasureTile(type, treasures_[treasure_index]);

    treasure_index++;
    vector.push_back(tile);
  }
}

bool Game::isCorner(size_t row_index, size_t col_index)
{
  return !(row_index % (BOARD_SIZE - 1)) && !(col_index % (BOARD_SIZE - 1));
}

bool Game::isInMoveableLine(size_t row_index, size_t col_index)
{
  return (row_index % 2 == 1 || col_index % 2 == 1);
}

void Game::fillTreasures()
{
  size_t id = 1;
  for(std::string treasure_name : TREASURE_NAMES)
  {
    Treasure* treasure = new Treasure(treasure_name, id);

    treasures_.push_back(treasure);
    id++;
  }
}

void Game::addPlayer(PlayerColor color)
{
  Player* player = new Player{color};

  players_.push_back(player);
}

void Game::nextPlayer()
{
  current_player_index_ = (current_player_index_ + 1) % players_.size();
}

Player* Game::getCurrentPlayer()
{
  return players_[current_player_index_];
}

void Game::distributeTreasures()
{
  std::vector<Treasure*> temp_treasures = treasures_;
  for (size_t cards_dealt = 0; cards_dealt < treasures_.size();)
  {
    for (Player* player : players_)
    {
      size_t next_card_index = Oop::Random::getInstance().getRandomCard(temp_treasures.size());
      player->getCoveredStackRef().push_back(temp_treasures[next_card_index - 1]);
      temp_treasures.erase(temp_treasures.begin() + next_card_index - 1);
      cards_dealt++;
    }
  }
}

void Game::deleteBoard()
{
  for (std::vector<Tile*> row : board_)
  {
    for (Tile* tile : row)
    {
      delete tile;
    }
  }
}

void Game::deleteTreasures()
{
  for (Treasure* treasure : treasures_)
  {
    delete treasure;
  }
}

void Game::deleteFreeTile()
{
  delete free_tile_;
}

void Game::deletePlayers()
{
  for (Player* player : players_)
  {
    delete player;
  }
}

void Game::printGame()
{
  std::vector<std::string> ui_lines = generateUILines();

  std::cout << ui_lines[0] << std::endl;
  std::cout << ui_lines[1] << std::endl;
  std::cout << UI_COLUMN_LABELS << std::endl;
  printBoard();
  std::cout << ui_lines[2] << std::endl;
  std::cout << ui_lines[3] << std::endl;
}

std::vector<std::string> Game::generateUILines()
{
  size_t player_index_titles = 0;
  size_t player_index_treasures = 0;

  size_t title_row_at = 0;
  size_t title_row_mod = 2;

  size_t arrow_base_at = 0;
  size_t arrow_base_mod = 3;

  std::vector<std::string> lines;

  for (size_t index = 0; index < 4; index++)
  {
    std::string line = "                                                                       ";
    if (index % title_row_mod == title_row_at)
    {
      addPlayerTitlesToLine(line, player_index_titles);
    }
    else
    {
      addTreasureCountersToLine(line, player_index_treasures);
    }

    if (index % arrow_base_mod == arrow_base_at)
    {
      addArrowBasesToLine(line);
    }
    else
    {
      if (index == 1)
      {
        addArrowTipsToLine(line, Direction::BOTTOM);
      }
      else if (index == 2)
      {
        addArrowTipsToLine(line, Direction::TOP);
      }
    }
    line.erase(line.find_last_not_of(" ") + 1);
    lines.push_back(line);
  }

  return lines;
}

void Game::addPlayerTitlesToLine(std::string& line, size_t& player_index)
{
  for (size_t times = 0; times < 2; times++)
  {
    if (player_index < players_.size())
    {
      std::string title = UI_PLAYER_BASE;
      title += players_[player_index]->getPlayerColorAsString();
      title += "(";
      title += static_cast<char>(players_[player_index]->getPlayerColor());
      title += ")";

      line.replace(UI_PLAYER_TITLE_OFFSET * times, title.length(), title);
      player_index++;
    }
  }
}

void Game::addTreasureCountersToLine(std::string& line, size_t& player_index)
{
  for (size_t times = 0; times < 2; times++)
  {
    if (player_index < players_.size())
    {
      std::string treasure_counter = UI_TREASURE_COUNTER;
      treasure_counter.append(std::to_string(players_[player_index]->getNrFoundTreasures()));
      treasure_counter.append("/");
      treasure_counter.append(std::to_string(treasures_.size() / players_.size()));

      line.replace(UI_PLAYER_TITLE_OFFSET * times, treasure_counter.length(), treasure_counter);
      player_index++;
    }
  }
}

void Game::addArrowBasesToLine(std::string& line)
{
  line.replace(UI_ARROW_OFFSET, UI_ARROW_BASES.length(), UI_ARROW_BASES);
}

void Game::addArrowTipsToLine(std::string& line, Direction direction)
{
  std::string arrows;
  if (direction == Direction::BOTTOM)
  {
    arrows = UI_DOWN_ARROWS;
  }
  else if (direction == Direction::TOP)
  {
    arrows = UI_UP_ARROWS;
  }
  line.replace(UI_ARROW_OFFSET, arrows.length(), arrows);
}

void Game::printBoard()
{
  size_t row_label_index = 2;
  size_t line_index = 0;
  size_t row_index = 1;
  for (std::vector<Tile*> row : board_)
  {
    std::vector<std::vector<std::string>> tile_strings;
    for (Tile* tile : row)
    {
      tile_strings.push_back(tile->getTileString());
    }

    for (size_t tile_line_index = 0; tile_line_index < TILE_HEIGHT; tile_line_index++)
    {
      bool print_arrow = false;

      printLeftUI(row_index, line_index, row_label_index, print_arrow);
      printTilesOfLine(tile_strings, tile_line_index);
      printRightUI(print_arrow);
      line_index++;
    }
  }
}

void Game::printLeftUI(size_t& row_index, size_t line_index, size_t& row_label_index, bool& print_arrow)
{
  if (line_index == row_label_index)
  {
    row_label_index += 5;
    if (row_index % 2 == 0)
    {
      print_arrow = true;
      std::cout << UI_ARROW_RIGHT;
    }
    else
    {
      std::cout << "   ";
    }
    std::cout << row_index++;
  }
  else
  {
    std::cout << "    ";
  }
}

void Game::printTilesOfLine(std::vector<std::vector<std::string>>& tile_strings, size_t tile_line_index)
{
  for (std::vector<std::string> tile_rows : tile_strings)
  {
    std::cout << tile_rows[tile_line_index];
  }
}

void Game::printRightUI(bool print_arrow)
{
  if (print_arrow)
  {
    std::cout << UI_ARROW_LEFT;
  }
  std::cout << std::endl;
}

void Game::invalidCommand(std::string command)
{
  std::cout << COMMAND_INVALID << "\"" << command << "\"" << std::endl;
}

void Game::invalidParameter(std::string parameter)
{
  std::cout << COMMAND_INVALID_PARAMETER << "\"" << parameter << "\"" << std::endl;
}

void Game::wrongNumberArguments()
{
  std::cout << COMMAND_WRONG_NUMBER_ARGUMENTS << std::endl;
}

void Game::commandTakesNoArguments()
{
  std::cout << COMMAND_TAKES_NO_ARGUMENTS << std::endl;
}

void Game::commandNotAllowed(std::vector<std::string> tokens)
{
  std::string invalid_command = "";
  for (size_t index = 0; index < tokens.size(); index++)
  {
    invalid_command += (tokens[index] + " ");
  }
  std::cout << "\"" << invalid_command.substr(0, invalid_command.length() - 1)
            << "\"" << COMMAND_NOT_ALLOWED << std::endl;
}

void Game::impossibleMove()
{
  std::cout << IMPOSSIBLE_MOVE << std::endl;
}

void Game::moveNotAllowed(std::vector<std::string> tokens)
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
