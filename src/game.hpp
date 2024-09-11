#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "player.hpp"

enum GameMode{PVP, PVE, EVE};

class Game
{
    Board *board;
    Player players[2];
    GameMode gameMode;

    void setPlayers();

    public:
        Game();
        ~Game();
        void restartBoard();
        void loopGame();
        void exitGame();
        void enterGame();
        void newBoard();
        void setGameMode(GameMode gameMode);
};

#endif //GAME_HPP