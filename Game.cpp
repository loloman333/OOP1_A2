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

// TODO: remove?
#include "Treasure.hpp"

Game::Game() {}

Game& Game::instance()
{
  static Game instance_;
  return instance_;
}

void Game::run()
{
  fillTreasures();
  // gameStart(); //Nagy
  distributeTreasures(); //Grill
  // fillBoard(); //Killer

  // While something
  // while (true)
  // {
  //  print();
  //  playRound();
  // }
}

void Game::fillBoard()
{

  std::vector<char> player_colors = {'B', 'G', 'Y', 'R'};
  size_t treasure_index = 0;

  //fillStaticTiles();
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
          /*TODO*/
          board_[row_index].push_back(new TreasureTile{nullptr});
          treasure_index++;
        }
      }
    }
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
      std::cout << "Player: " << player->getPlayerColor() << "; Card: " << temp_treasures[next_card_index - 1]->getName() << std::endl;
      temp_treasures.erase(temp_treasures.begin() + next_card_index - 1);
      cards_dealt++;

    }
  }
}