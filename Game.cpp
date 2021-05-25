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
#include "CommandMaster.hpp"
#include "PrintMaster.hpp"

#include <algorithm>

Game::Game(){
  command_master_ = new CommandMaster(*this);
  print_master_ = new PrintMaster(*this);
}

Game::~Game()
{
  deleteFreeTile();
  deleteBoard();
  deleteTreasures();
  deletePlayers();
  delete command_master_;
  delete print_master_;
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

    while (gameIsRunning())
    {
      print_master_->printGameIfNecessary();
      playRound();
    }

  }
  catch (std::bad_alloc)
  {
    return EXIT_MEMORY_ERROR;
  }
  return EXIT_DEFAULT;
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
    input_vector = command_master_->tokenize(input);
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
  Player* player = getCurrentPlayer();
  std::string current_output = player->getPlayerColorAsString();
  std::transform(current_output.begin(), current_output.end(), current_output.begin(), ::toupper);
  current_output += " > ";

  bool stop = false;
  while(!stop)
  {
    std::cout << current_output;
    stop = command_master_->handleCommand();
  }
  command_master_->reset();
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

void Game::quitGame()
{
  quit_ = true;
}

bool Game::gameIsRunning()
{
  return !quit_;
}

Tile* Game::getFreeTile()
{
  return free_tile_;
}

void Game::setFreeTile(Tile* tile)
{
  free_tile_ = tile;
}

std::vector<std::vector<Tile*>>& Game::getBoard()
{
  return board_;
}

std::vector<Player*>& Game::getPlayers()
{
  return players_;
}

std::vector<Treasure*>& Game::getTreasures()
{
  return treasures_;
}

CommandMaster* Game::getCommandMaster()
{
  return command_master_;
}

PrintMaster* Game::getPrintMaster()
{
  return print_master_;
}

