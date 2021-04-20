//---------------------------------------------------------------------------------------------------------------------
// Player.hpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_PLAYER_HPP
#define A2_PLAYER_HPP

#include "Treasure.hpp"

#include <vector>

class Player
{

  private:
    std::vector<Treasure*> covered_stack_;
    size_t nr_found_treasures_;

  public: 
    Player();

    std::vector<Treasure*>& getCoveredStackRef();
    size_t getNrFoundTreasures();
    void setNrFoundTreasures(size_t nr_found_treasures);
};

#endif //A2_PLAYER_HPP