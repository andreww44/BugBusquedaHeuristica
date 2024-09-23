#include <iostream>
#include <cstdint>

#include "board.hpp"

Board::Board(){

    board[White] = 0x8181818181818181ULL;
    board[Black] = 0xff000000000000ffULL;
    maskBoard[White] = ~board[White];
    maskBoard[Black] = ~board[Black];
    turn = White;
    oneMask = 1ULL;
    zeroMask = 0ULL;
}

Board::~Board() = default;

bool Board::isLegalMove(int position){
    //std::cout << "Wb" << std::bitset<64>(wBoard) << std::endl;
    if(position < 0 || position > BOARD_SIZE)
        return false;
    if (turn == White && ( (board[White] |(board[Black] & maskBoard[Black])) & (oneMask << position) ))          
        return false;
    if (turn == Black && ( (board[Black] |(board[White] & maskBoard[White])) & (oneMask << position) ))
        return false;
    return true;
}

bool Board::isEating(int position){
    //turn
    //Comer solo a la derecha
    int y = position/N;
    int x = position%N;

    std::cout<< "x = " << x << "y = " << y << std::endl;  

    //Seis direcciones
    //x = 3 y = 3 
    // x = 8 -3 = 5
    for(int i = 0; i < N-x; i++){

        if(board[turn] & maskBoard[turn] & oneMask << position + i ){
            std::cout << "Existe" << std::endl;
            break;
        }
        else
        {
            std::cout << "No Hay" << std::endl;
        }
    }
    

    return false;
}

bool Board::makeMove(int position){
    if (position < 0 || position >= BOARD_SIZE) {
        return false;
    }
    else if(isLegalMove(position)){
        board[turn] |= (oneMask << position);
        if(isEating(position)){
            std::cout<< "Comiste "<<std::endl ;
        }
        turn = (turn == White) ? Black : White;
        return true;
    }
    return false;
}

bool Board::isValidInLimits(int x, int y){
    return x >= 0 && x < N && y >=0 && y < N;
}

bool Board::existsWayDfs(MARK color, U64 map, U64& visit, int x, int y, int pf){
    //std::cout<< "DFS" << std::endl;
    if(!isValidInLimits(x, y)){
        return false;
    }

    int position = x*N + y;

    if((visit & (oneMask << position )) || !(map &(oneMask << position))){
        return false;
    }

    visit |= (oneMask << position);

    if(color == White){
        if(x == pf){
            return true;
        }
    }
    if(color == Black){
        if(y == pf){
            return true;
        }
    }
    
    // Revisa Derecha
    if(y + 1 < N && existsWayDfs(color, map, visit, x, y+1, pf)){
        return true;
    }

    // Revisa Arriba
    if(x-1 >= 0 && existsWayDfs(color, map, visit, x-1, y, pf)){
        return true;
    }

    // Revisa hacia abajo
    if(x + 1 < N && existsWayDfs(color, map, visit, x + 1, y, pf)){
        return true;
    }

    //Revisa Izquierda

    if(y - 1 >= 0 && existsWayDfs(color, map, visit, x, y-1, pf)){
        return true;
    }        
    return false;
}

void Board::print(){
    U64 wTable = board[White] & maskBoard[White];
    U64 bTable = board[Black] & maskBoard[Black];


    //U64 table = wTable | bTable; 
    std::cout << "Tablero Troll" << std::endl;
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++){
            if(wTable&(oneMask << (j+ (i*N)))){
                std::cout<<"W ";
            }
            else if(bTable&(oneMask << (j+ (i*N)))){
                std::cout<<"B ";
            }
            else{
                std::cout<< "* "; 
            }
        }
        std::cout<< "\n"; 
    }
    std::cout << std::endl;
}

bool Board::hasWhiteWon(){
    U64 map = board[White] & maskBoard[White];
    U64 visit = zeroMask;
    for(int i = 0; i < N; i++){
        if(existsWayDfs(White, map, visit, 0,i,7)){
            return true;
        }
    }
    return false;
}

bool Board::hasBlackWon(){
    U64 map = board[Black] & maskBoard[Black];
    U64 visit = zeroMask;
    for(int i = 0; i < N; i++){
        if(existsWayDfs(Black, map, visit, i,0,7)){
            return true;
        }
    }
    return false; 
}

MARK Board::getMark(){
    return turn;
}