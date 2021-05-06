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

void Game::run()
{
  fillTreasures();

  gameStart(); //Nagy
  fillBoard(); //Killer
  distributeTreasures(); //Grill

  // While something
  while (true)
  {
    print();
    playRound();
  }
}

void Game::gameStart()
{
  std::cout << UI_WELCOME << std::endl;

  std::string input;
  size_t playerCount = 0;
  while (playerCount == 0)
  {
    std::cout << UI_PLAYER_COUNT;
    std::getline(std::cin, input);
    if(input == "2")
    {
      playerCount = 2;
    }
    else if(input == "3")
    {
      playerCount = 3;
    }
    else if(input == "4")
    {
      playerCount = 4;
    }
    else
    {
      std::cout << UI_WRONG_COUNT << std::endl;
    }
  }
  std::vector<char> player_colors = {'B', 'G', 'Y', 'R'};
  for(size_t i = 0; i < playerCount; i++)
  {
    addPlayer(player_colors.back());
    player_colors.pop_back();
  }
}

void Game::playRound()
{
  Player* player = getCurrentPlayer();
  std::string currentOutput = "";
  
  switch (player->getPlayerColor())
  {
  case 'R':
    currentOutput = "RED > ";
    break;
  case 'G':
    currentOutput = "GREEN > ";
    break;
  case 'B':
    currentOutput = "BLUE > ";
    break;
  case 'Y':
    currentOutput = "YELLOW > ";
    break;
  }

  while(true)
  {
    std::cout << currentOutput;
    std::string command;
    std::cin >> command;
    if(std::cin.eof())
    {
      exit(0);
    }
  }

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
  std::vector<char> player_colors = {'R', 'Y', 'G', 'B'};

  for (size_t row_index = 0; row_index < BOARD_SIZE; row_index++)
  {
    board_.push_back(std::vector<Tile*>{});

    for (size_t col_index = 0; col_index < BOARD_SIZE; col_index++)
    {
      if (row_index % 2 == 1 || col_index % 2 == 1)
      {
        board_[row_index].push_back(nullptr);
      }
      else
      {
        if (isCorner(row_index, col_index))
        {
          Tile* tile = new StartTile{player_colors[player_index]};
          if (!tile)
          {
            exit(1);
          }

          board_[row_index].push_back(tile);
          
          if (player_index < players_.size())
          {
            tile->addPlayer(players_[player_index]);
          }

          player_index++;
        }
        else
        {
          TreasureTile* treasure_tile = new TreasureTile{treasures_[treasure_index]};
          if (!treasure_tile)
          {
            exit(1);
          }
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
    NormalTile* normal_tile = new NormalTile{type};
    if(!normal_tile)
    {
      exit(1);
    }
    vector.push_back(normal_tile);
  }
}

void Game::addNewTreasureTilesToVector(std::vector<Tile*>& vector, TileType type, size_t count, size_t& treasure_index)
{
  for (size_t i = 0; i < count; i++)
  { 
    Tile* tile = new TreasureTile{type, treasures_[treasure_index]};
    if(!tile)
    {
      exit(1);
    }

    treasure_index++;
    vector.push_back(tile);
  }
}

bool Game::isCorner(size_t row_index, size_t col_index)
{
  return !(row_index % (BOARD_SIZE - 1)) && !(col_index % (BOARD_SIZE - 1));
}

void Game::fillTreasures()
{
  size_t id = 1;
  for(std::string treasure_name : TREASURE_NAMES)
  {
    Treasure* treasure = new Treasure(treasure_name, id);
    if(!treasure)
    {
      exit(1);
    }
    treasures_.push_back(treasure);
    id++;
  }
}

void Game::addPlayer(char color)
{
  Player* player = new Player{color};
  if(!player)
  {
    exit(1);
  }
  players_.push_back(player);
}

void Game::nextPlayer()
{
  currentPlayerIndex_++;
}

Player* Game::getCurrentPlayer()
{
  return players_[currentPlayerIndex_];
}

void Game::distributeTreasures()
{
  std::vector<Treasure*> temp_treasures = treasures_;
  for (size_t cards_dealt = 0; cards_dealt < treasures_.size(); cards_dealt++)
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

void Game::print()
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
      std::string title;
      switch (players_[player_index]->getPlayerColor())
      {
      case 'R':
        title = UI_PLAYER_RED;
        break;
      case 'Y':
        title = UI_PLAYER_YELLOW;
        break;
      case 'G':
        title = UI_PLAYER_GREEN;
        break;
      case 'B':
        title = UI_PLAYER_BLUE;
        break;
      default:
        break;
      }
      line.replace(58 * times, title.length(), title);
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

      line.replace(58 * times, treasure_counter.length(), treasure_counter);
      player_index++;
    }
  }
}

void Game::addArrowBasesToLine(std::string& line)
{
  line.replace(17, UI_ARROW_BASES.length(), UI_ARROW_BASES);
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
  line.replace(17, arrows.length(), arrows);
}

// Print the actual board
void Game::printBoard()
{
  size_t row_label_index = 2;
  size_t line_index = 0;
  size_t row_index = 1;
  for (std::vector<Tile*> row : board_)
  {
    std::vector<std::vector<std::string>> tile_strings{};
    for (Tile* tile : row)
    {
      tile_strings.push_back(tile->getTileString());
    }
    
    for (size_t tile_line_index = 0; tile_line_index < TILE_HEIGHT; tile_line_index++)
    {
      bool print_arrow = false;

      // Print the row labels
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

      // Print the tiles
      for (std::vector<std::string> tile_rows : tile_strings)
      {
        std::cout << tile_rows[tile_line_index];
      }

      // Print right arrows
      if (print_arrow)
      {
        std::cout << UI_ARROW_LEFT;
      }
      std::cout << std::endl;

      line_index++;
    } 
  }
}