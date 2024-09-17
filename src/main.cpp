#include <iostream>
#include <string>
#include <vector>
#include <bitset>

//#include "board.hpp"
#include "game.hpp"

//Funcion que imprime ambos tableros
int main()
{
    Game _game;;
    _game.enterGame();
    _game.loopGame();
    _game.exitGame();
    return 0;
}