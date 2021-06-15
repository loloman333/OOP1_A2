//----------------------------------------------------------------------------------------------------------------------
// AIMaster.hpp
//
// TODO
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//----------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_AIMASTER_HPP
#define A2_AIMASTER_HPP

#include <stddef.h>

class Game;
class Player;

class AIMaster
{
private:
  Game& game_;

public:
  AIMaster(Game& game);

  ~AIMaster() = default;
  AIMaster(const AIMaster& ai_master) = delete;
  AIMaster& operator=(const AIMaster& ai_master) = delete;

  bool isConnected(Player* current_player, size_t to_row, size_t to_column);
  void playAI();
};

#endif // A2_AIMASTER_HPP
