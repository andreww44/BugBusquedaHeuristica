#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "player.hpp"

enum GameMode{PVP, PVE, EVE};

class Game
{
    Board *board;
    Player iaPlayer;
    GameMode gameMode;

    void setGameMode();

    public:
        Game();
        ~Game();
        void loopGame();
        void exitGame();
        void enterGame();
        void newBoard();
        bool hasOneWin(); 
        
};

#endif //GAME_HPP