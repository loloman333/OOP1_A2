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
#include <vector>

const std::vector<std::string> TREASURE_NAMES{
  "Totenkopf",
  "Schwert",
  "Goldsack",
  "Schlüsselbund",
  "Sombrero",
  "Ritterhelm",
  "Buch",
  "Krone",
  "Schatztruhe",
  "Kerzenleuchte",
  "Schatzkarte",
  "Goldring",
  "Eule",
  "Hofnarr",
  "Eidechse",
  "Käfer",
  "Flaschengeist",
  "Kobold",
  "Schlange",
  "Geist",
  "Fledermaus",
  "Spinne",
  "Ratte",
  "Motte"};

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
