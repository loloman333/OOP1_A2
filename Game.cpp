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

Game::Game() {}

Game::~Game()
{
  deleteBoard();
  deleteTreasures();
}

Game& Game::instance()
{
  static Game instance_;
  return instance_;
}

void Game::run()
{
  fillTreasures();

  // TODO: remove once gameStart works
  addPlayer(new Player{'R'});
  addPlayer(new Player{'Y'});
  
  // gameStart(); //Nagy
  distributeTreasures(); //Grill
  fillBoard(); //Killer

  // While something
  // while (true)
  // {
  //  print();
  //  playRound();
  // }
}

void Game::fillBoard()
{
  fillStaticTiles();
  fillVariableTiles();
}

void Game::fillStaticTiles()
{
  std::vector<char> player_colors = {'B', 'G', 'Y', 'R'};
  size_t treasure_index = 0;

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
          board_[row_index].push_back(new StartTile{player_colors.back()});
          player_colors.pop_back();
        }
        else
        {
          board_[row_index].push_back(new TreasureTile{treasures_[treasure_index]});
          treasure_index++;
        }
      }
    }
  }
}

void Game::fillVariableTiles()
{
  std::vector<Tile*> tiles;
  addNewTilesToVector(tiles, TileType::L, 11);
  addNewTilesToVector(tiles, TileType::I, 11);
  addNewTilesToVector(tiles, TileType::T, 12);

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
}

void Game::addNewTilesToVector(std::vector<Tile*>& vector, TileType type, size_t count)
{
  for (size_t i = 0; i < count; i++)
  {
    vector.push_back(new NormalTile{type});
  }
}

bool Game::isCorner(size_t row_index, size_t col_index)
{
  return !(row_index % (BOARD_SIZE - 1)) && !(col_index % (BOARD_SIZE - 1));
}

void Game::fillTreasures()
{
  std::ifstream file(TREASURE_PATH);
  std::string treasure;
  size_t id = 1;
  while (file >> treasure)
  {
    treasures_.push_back(new Treasure(treasure, id));
    id++;
  }
}

void Game::addPlayer(Player* player)
{
  players_.push_back(player);
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