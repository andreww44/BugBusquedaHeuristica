#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "board.hpp"
#include "TTEntry.h"



class Player
{
private:

public:
    Player();
    ~Player();
    int negaMax(Board node, int depth, int &bestPosition);
    int alphaBeta(Board node, int maxDepth, int depth, int alpha,int beta, int &bestPosition);
    int interativeDeepening(Board node, int maxDepth, int &bestPosition);
    int alphabetaTT(Board node, int maxDepth, int depth,int alpha, int beta, int &bestPosition);
    
    //La idea de la clase player es que exista la ia y tambien exista para jugar de dos persoans
};




#endif //PLAYER_HPP