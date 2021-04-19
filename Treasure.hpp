//---------------------------------------------------------------------------------------------------------------------
// Treasure.hpp
//
// Class for Treasures
//
// Authors: Triochter Bande (Grill Matthias, Killer Lorenz, Nagy Lukas)
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef A2_TREASURE_HPP
#define A2_TREASURE_HPP

#include <string>

class Treasure
{
  private:
    std::string name_;
    size_t treasure_id_;
    bool found_ = false;

  public:
    Treasure(std::string name, size_t treasure_id);

    std::string getName();
    size_t getTreasureId();
    bool getFound();

    void setFound(bool found);
};


#endif //A2_TREASURE_HPP
