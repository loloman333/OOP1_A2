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

#include "Tile.hpp"

class Game
{
  private:

    std::vector<std::vector<Tile>> board_;

    Game();
    Game(const Game&); 
    Game& operator = (const Game&); 

  public:
    static Game& instance();
    ~ Game() = default;

    void run();
    void gameStart();
    void distributeTreasures();
    void fillBoard();
    void print();
    void playRound();  
};

#endif //A2_GAME_HPP
