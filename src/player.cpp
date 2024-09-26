#include <iostream>
#include <cstdint>

#include "player.hpp"

Player::Player(){
    
}

Player::~Player() = default;

int Player::negaMax(Board node, int depth, int &bestPosition) {
    int maxDepth = 9;
    node.print();
    if (node.endGame() || depth == maxDepth) {
        
        return node.evaluateBoard(depth);
    }

    int bestValue = -10000, dummy;  // Variable para el valor de posición en las llamadas recursivas

    // Itera sobre todas las posibles jugadas legales
    for (int position : node.generateAllLegalMoves()) {
        Board child(node);  // Crea una copia del tablero actual
        if(child.makeMove(position)){
            // Llama recursivamente a negamax
            int value = -negaMax(child, depth + 1, dummy);
            if (value > bestValue) {
                bestValue = value;
                bestPosition = position;
            }
        }  // Realiza la jugada   
    }
    return bestValue;  // Devuelve el mejor valor encontrado
}

int Player::alphaBeta(Board node, int maxDepth, int depth, int alpha, int beta, int &bestPosition){
    
    node.print();
    if (node.endGame() || depth == maxDepth) {
        return node.evaluateBoard(depth);
    }

    int bestValue = -10000, dummy; 

    for (int position : node.generateAllLegalMoves()) {
        Board child(node);  // Crea una copia del tablero actual
        if(child.makeMove(position)){
            // Llama recursivamente a negamax
            int value = -alphaBeta(child, maxDepth, depth+1, -beta, -alpha ,dummy);
            if (value > bestValue) {
                bestValue = value;
                bestPosition = position;
                if(value > alpha) alpha = value;
                if(alpha >= beta)break;
            }
        }  // Realiza la jugada   
    }
    return bestValue;
}

int Player::interativeDeepening(Board node, int maxDepth, int &bestPosition){
    int value;
    for (int depth = 0; depth < maxDepth; depth++)
    {
        value = alphaBeta(node, depth, 0, -10000000, 10000000, bestPosition);
    }
    return value;
    
}