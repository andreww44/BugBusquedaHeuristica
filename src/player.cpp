#include <iostream>
#include <cstdint>

#include "player.hpp"

TranspositionTable TT;

Player::Player(){
    
}



Player::~Player() = default;


void Player::reset(){
    maxdepth = 0;
    nodesvistit = 0;
    iterac = 0;
}

int Player:: getNV(){
    return nodesvistit;
}
int Player:: getMD(){
    return maxdepth;
}
int Player:: getIT(){
    return iterac;
}
int Player:: getScore(){
    return puntaje;
}
int Player::negaMax(Board node, int depth, int &bestPosition) {
    int maxDepth = 9;
    maxdepth = depth;
    nodesvistit++;
    if (node.endGame() || depth == maxDepth) {
        return node.evaluateBoard(depth);
    }
    int bestValue = -10000, dummy; 

    for (int position : node.generateAllLegalMoves()) {
        Board child(node.getWhiteBoard(), node.getBlackBoard(), node.getActiveTurn());
        if(child.makeMove(position)){
        
            int value = -negaMax(child, depth + 1, dummy);
            if (value > bestValue) {
                bestValue = value;
                bestPosition = position;
            }
        }  // Realiza la jugada   
    }
    puntaje+= bestValue;
    return bestValue;  // Devuelve el mejor valor encontrado
}

int Player::negaScout(Board node, int depth, int &bestPosition, int alpha, int beta) {
    int maxDepth = 9;
    maxdepth = depth;
    nodesvistit++;
    if (node.endGame() || depth == maxDepth) {
        return node.evaluateBoard(depth);
    }

    int bestValue = -10000, dummy;
    bool firstChild = true;

    for (int position : node.generateAllLegalMoves()) {
        Board child(node.getWhiteBoard(), node.getBlackBoard(), node.getActiveTurn());
        if (child.makeMove(position)) {
            
            int score;
            if (firstChild) {
                score = -negaScout(child, depth + 1, dummy, -beta, -alpha);
                firstChild = false;
            } else {
                score = -negaScout(child, depth + 1, dummy, -alpha - 1, -alpha);
                if (alpha < score && score < beta) {
                    score = -negaScout(child, depth + 1, dummy, -beta, -alpha);
                }
            }

            if (score > bestValue) {
                bestValue = score;
                bestPosition = position;
            }
            alpha = std::max(alpha, bestValue);
            if (alpha >= beta) {
                break; 
            }
        }
    }
    puntaje+= bestValue;
    return bestValue;
}

int Player::alphaBeta(Board node, int maxDepth, int depth, int alpha, int beta, int &bestPosition){
    maxdepth = depth;
    nodesvistit++;
    if (node.endGame() || depth == maxDepth) {
        return node.evaluateBoard(depth);
    }

    int bestValue = -10000, dummy; 

    for (int position : node.generateAllLegalMoves()) {
        Board child(node.getWhiteBoard(), node.getBlackBoard(), node.getActiveTurn());  // Crea una copia del tablero actual
        if(child.makeMove(position)){
            
            int value = -alphaBeta(child, maxDepth, depth+1, -beta, -alpha ,dummy);
            child.undoMove(position);
            if (value > bestValue) {
                bestValue = value;
                bestPosition = position;
                if(value > alpha) alpha = value;
                if(alpha >= beta)break;
            }
        }   
    }
    puntaje+= bestValue;
    return bestValue;
}

int Player::interativeDeepening(Board node, int maxDepth, int &bestPosition){
    int value;
    for (int depth = 0; depth < maxDepth; depth++)
    {
        iterac++;
        value = alphaBeta(node, depth, 0, -10000000, 10000000, bestPosition);
    }
    puntaje+= value;
    return value; 
}

int Player::alphabetaTT(Board node, int maxDepth, int depth,int alpha, int beta, int &bestPosition){

    TTEntry ttEntry = TT.get(node);
    if (ttEntry.isValid()){
        if(ttEntry.getDepth() >= depth) {
            if (ttEntry.isExact()){
                return ttEntry.getValue();
            }
            if (ttEntry.isLower()) {
                alpha = std::max(alpha, ttEntry.getValue());
            } else if (ttEntry.isUpper()){
                beta = std::min(beta, ttEntry.getValue());
            }
            if (alpha >= beta){
                return ttEntry.getValue();
            }
        }
    }

    if(node.endGame() || depth == maxDepth)
        return node.evaluateBoard(depth);

    int bestValue= -10000, dummy;  // dummy: variable para descartar las posiciones en las llamadas recursivas
    int al = alpha;
    // Iteramos sobre todas las posibles jugadas legales
    for (int position : node.generateAllLegalMoves()) {
        Board child(node);
        child.makeMove(position);

        int value = -alphaBeta(child, maxDepth, depth+1, -beta, -al, dummy);
        if (value > bestValue) {
            bestValue = value;
            bestPosition = position;
            if (value > al) al = value;
            if (al >= beta) break;
        }
    }
    bool lower = false, exact = false, upper = false;
    if (bestValue <= alpha)
        upper = true;
    else if (bestValue >= beta)
        lower = true;
    else
        exact = true;
    TT.store(TTEntry(bestValue, depth, lower, exact, upper, bestPosition), node);
    puntaje+= bestValue;
    return bestValue;
}

int Player::MTDf(Board node, int f, int maxDepth, int &bestPosition) {
    
    int upperBound = 10000000;  
    int lowerBound = -10000000;  
    
    while (lowerBound < upperBound) {
        iterac++;
        int beta = max(f, lowerBound+1);  
        f = alphabetaTT(node, maxDepth, 0, beta - 1, beta, bestPosition);  
        
        if (f < beta) {
            upperBound = f;  
        } else {
            lowerBound = f; 
        }
    }
    puntaje+= f;
    return f;
}

int Player::max(int f, int lw){
    if (f > lw)
        return f;
    if(lw > f)
        return lw;
    return lw;
}