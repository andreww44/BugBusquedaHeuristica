#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "board.hpp"
#include "TTEntry.h"



class Player
{
private:
    int nodesvistit = 0;
    int maxdepth = 0;
    int iterac = 0;
    int puntaje = 0;

public:
    Player();
    ~Player();
    int negaMax(Board node, int depth, int &bestPosition);
    int negaScout(Board node, int depth, int &bestPosition, int alpha, int beta);
    int alphaBeta(Board node, int maxDepth, int depth, int alpha,int beta, int &bestPosition);
    int interativeDeepening(Board node, int maxDepth, int &bestPosition);
    int alphabetaTT(Board node, int maxDepth, int depth,int alpha, int beta, int &bestPosition);
    int MTDf(Board node, int f, int maxDepth, int &bestPosition);
    int max(int f, int lb);
    void reset();
    int getNV();
    int getMD();
    int getIT();
    int getScore();
    
    
    //La idea de la clase player es que exista la ia y tambien exista para jugar de dos persoans
};




#endif //PLAYER_HPP