//---------------------------------------------------------------------------------------------------------------------
// Player.hpp
//
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_PLAYER_HPP
#define A2_PLAYER_HPP

#include <vector>
#include <string>

class Treasure;

enum class PlayerColor {RED = 'R', YELLOW = 'Y', BLUE = 'B', GREEN = 'G'};

class Player
{

  private:
    std::vector<Treasure*> covered_stack_;
    size_t nr_found_treasures_;
    PlayerColor player_color_;

  public: 
    Player(PlayerColor player_color);

    std::vector<Treasure*>& getCoveredStackRef();
    size_t getNrFoundTreasures();
    PlayerColor getPlayerColor();
    std::string getPlayerColorAsString();

    static const std::vector<PlayerColor> player_colors_; 

    void setNrFoundTreasures(size_t nr_found_treasures);
    void setPlayerColor(PlayerColor player_color);
};

#endif //A2_PLAYER_HPP