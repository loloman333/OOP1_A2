//---------------------------------------------------------------------------------------------------------------------
// Item.cpp
//
// Class for Item
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#include "Item.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "PrintMaster.hpp"
#include "ItemTile.hpp"

Item::Item(ItemType item_type) : item_type_{item_type} {};

ItemType Item::getItemType()
{
  return item_type_;
}

std::string Item::getItemTypeAsString()
{
  switch (item_type_)
  {
  case ItemType::BRICKS:
    return "BRI";

  case ItemType::DYNAMITE:
    return "DYN";

  case ItemType::ROPE:
    return "ROP";

  case ItemType::LADDER:
    return "LAD";
  }
}

bool Item::getFound()
{
  return found_;
}

void Item::setFound(bool found)
{
  found_ = found;
}

void Item::use()
{
  Game& game = Game::instance();
  switch (item_type_)
  {
  case ItemType::BRICKS:
    useBricks(game);
    break;
  case ItemType::DYNAMITE:
    useDynamite(game);
    break;
  case ItemType::LADDER:
    useLadder(game);
    break;
  case ItemType::ROPE:
    useRope(game);
    break;
  }
}

void Item::useBricks(Game& game)
{

}
void Item::useDynamite(Game& game)
{

}
void Item::useLadder(Game& game)
{
  game.getPrintMaster()->ladderUsed();
  game.getCurrentPlayer()->setUsingLadder(true);
}
void Item::useRope(Game& game)
{
  std::vector<std::vector<Tile*>>& board = game.getBoard();
  Player* current_player = game.getCurrentPlayer();
  Tile* current_tile = board[current_player->getRow()][current_player->getCol()];

  if (current_tile->getPlayers().size() > 1)
  {
    current_player->getItem()->setFound(false);
    current_player->setItem(nullptr);
    game.getPrintMaster()->printGameIfNecessary();

    for (PlayerColor color : Player::player_colors_)
    {
      if(current_tile->isPlayerColorOnTile(color) && color != current_player->getPlayerColor())
      {
        Player* player = current_tile->getPlayer(color);
        player->setTied(true);
        std::cout << ROPE_TIED_1 << player->getPlayerColorAsString() << ROPE_TIED_2 << std::endl;
      }
    }
  }
  else
  {
    std::cout << ROPE_NO_PLAYER << std::endl;
  }
}