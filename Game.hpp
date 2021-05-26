//---------------------------------------------------------------------------------------------------------------------
// Game.hpp
//
// Class for Game
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_GAME_HPP
#define A2_GAME_HPP

#include <vector>
#include <string>

const size_t BOARD_SIZE = 7;
const size_t EXIT_DEFAULT = 0;
const size_t EXIT_MEMORY_ERROR = 1;

class Tile;
class Player;
class Treasure;
class CommandMaster;
class PrintMaster;
enum class PlayerColor;
enum class TileType;
enum class Direction;

class Game
{
private:
  CommandMaster* command_master_;
  PrintMaster* print_master_;

  Game();
  Game(const Game&);
  Game& operator=(const Game&);

  std::vector<std::vector<Tile*>> board_;
  std::vector<Treasure*> treasures_;
  std::vector<Player*> players_;
  Tile* free_tile_;
  size_t current_player_index_ = 0;
  bool quit_ = false;
  bool bonus_items_ = false;

  bool gameIsRunning();

  // Preparations
  void gameStart();
  void addPlayer(PlayerColor color);
  void distributeTreasures();
  void fillBoard();
  void fillStaticTiles(size_t& treasure_index);
  void fillVariableTiles(size_t& treasure_index);
  void addNewItemTilesToVector(std::vector<Tile*>& vector);
  void addNewNormalTilesToVector(std::vector<Tile*>& vector, TileType type, size_t count);
  void addNewTreasureTilesToVector(std::vector<Tile*>& vector, TileType type, size_t count, size_t& treasure_index);
  bool isInMoveableLine(size_t row_index, size_t col_index);
  void fillTreasures();

  // Free memory
  void deleteTreasures();
  void deleteFreeTile();
  void deleteBoard();
  void deleteItemsFromPlayers();
  void deletePlayers();
  void deleteTile(Tile* tile);
  
  void playRound();

public:

static Game& instance();
  
  ~Game();
  CommandMaster* getCommandMaster();
  PrintMaster* getPrintMaster();

  int run();

  void nextPlayer();
  bool isCorner(size_t row_index, size_t col_index);
  std::vector<std::vector<Tile*>>& getBoard();
  std::vector<Player*>& getPlayers();
  std::vector<Treasure*>& getTreasures();
  Player* getCurrentPlayer();
  Tile* getFreeTile();
  bool getBonusItemsFlag();
  void setFreeTile(Tile* tile);
  void setBonus(bool choice);
  void quitGame();

};

#endif // A2_GAME_HPP
