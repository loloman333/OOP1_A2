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
    char player_color_;

  public: 
    Player(char player_color);

    std::vector<Treasure*>& getCoveredStackRef();
    size_t getNrFoundTreasures();
    char getPlayerColor();

    void setNrFoundTreasures(size_t nr_found_treasures);
    void setPlayerColor(char player_color);
};

#endif //A2_PLAYER_HPP