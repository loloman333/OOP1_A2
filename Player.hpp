//---------------------------------------------------------------------------------------------------------------------
// Player.hpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_PLAYER_HPP
#define A2_PLAYER_HPP

#include "Treasure.hpp" // [FB] is the include here necessary? would a forward decleration suffice? When is in necessary to include header files?

#include <vector>

class Player
{

  private:
    std::vector<Treasure*> covered_stack_;
    size_t nr_found_treasures_;
    char player_color_; // [FB] Would en enum create a cleaner implementation?
    // [FB] ry to reduce the number of hardcoded values. The player colors are closely connected to the players, there should be no need for other classes to care about which color can or can not exist. This logic/constraint should be taken over by the Player class.

  public: 
    Player(char player_color); // [FB] missing definitions/headers

    std::vector<Treasure*>& getCoveredStackRef();
    size_t getNrFoundTreasures();
    char getPlayerColor();

    void setNrFoundTreasures(size_t nr_found_treasures);
    void setPlayerColor(char player_color);
};

#endif //A2_PLAYER_HPP