#include <iostream>
#include <cstdint>
#include "board.hpp"

Board::Board(){

    board[White] = 0x8181818181818181ULL;
    board[Black] = 0xff000000000000ffULL;
    maskBoard[White] = ~board[White];
    maskBoard[Black] = ~board[Black];
    fullMask = maskBoard[White] | maskBoard[Black];
    
    turn = White;
    oneMask = 1ULL;
    zeroMask = 0ULL;

    winingBoard[Black] = 0x00FF000000000000ULL;
    winingBoard[White] = 0x4040404040404040ULL;
    std::bitset<64> bits(winingBoard[White]);
    std::cout <<  bits << std::endl;
}

U64 Board::getBlackBoard() const { return board[Black]; }
U64 Board::getWhiteBoard() const { return board[White]; }

MARK Board::getActiveTurn() const { return turn; }

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
    // Llama a la función para todas las direcciones
    for (int dir = 0; dir < 8; dir++) {
        eat(position, dir);
    }
    return true;
}

bool Board::eat(int position, int direction){
    int y = position / N;
    int x = position % N;
    int dy = DIRECTIONS[direction][0];
    int dx = DIRECTIONS[direction][1];

    // Nueva posición
    int newY = y + dy;
    int newX = x + dx;

    // Comprobar límites
    if(newY < 0 || newY >= N || newX < 0 || newX >= N){
        return false; // Fuera de límites
    }

    int newPosition = newY * N + newX; // Calcular nueva posición en el tablero

    MARK notTurn = (turn == White) ? Black : White;
    
    if(!((board[turn] & maskBoard[turn]) & (oneMask << newPosition))) {
        if(!((board[notTurn] & maskBoard[notTurn]) & (oneMask << newPosition))) {
            return false;
        }
        if(!eat(newPosition, direction)) {
            return false; 
        }
    }
    board[notTurn] &= ~(oneMask << newPosition); 
    board[turn] |= (oneMask << newPosition);     
    return true;
}

bool Board::makeMove(int position){
    if (position < 0 || position >= BOARD_SIZE) {
        return false;
    }
    else if(isLegalMove(position)){
        board[turn] |= (oneMask << position);
        if( isEating(position)){
            
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

int Board::evaluateBoard(int depth) {
    int score = 0;
    MARK currentPlayer = getMark();
    MARK opponent = (currentPlayer == White) ? Black : White;

    score += __builtin_popcountll(board[currentPlayer]);
    score -= __builtin_popcountll(board[opponent]);

    //Con un while contando las que estan al lado

    int fevaluate_1[9] = { 1, 2, 1,
                           3, 0, 3,
                           1, 2, 1 };

    int pos = 0;

    if(currentPlayer == Black){
        for (int i = 0; i < 6; i++)
        {
            if(board[currentPlayer] & maskBoard[currentPlayer] & (winingBoard[currentPlayer] << 8*i)){
                score +=10000;
            }
        } 
    }
    else{
        
        for (int i = 0; i < 6; i++)
        {
            if(board[currentPlayer] & maskBoard[currentPlayer] & (winingBoard[currentPlayer] << i)){
                score +=10000;
            }
        } 
    
    }

    for(int i = 0; i < BOARD_SIZE; i++){
        int x = pos%N;
        int y = pos/N;
        if(board[currentPlayer] & maskBoard[currentPlayer] & (oneMask << pos+1)){
            if(currentPlayer == Black){
                score+=10;
            }
            else{
                score+=6;
            }
        }
        else{
            score -=100;
        }
        if(board[currentPlayer] & maskBoard[currentPlayer] & (oneMask << pos-1)){
            if(currentPlayer == Black){
                score+=10;
            }
            else{
                score+=6;
            }
        }
        else{
            score -=100;
        }
        if(board[currentPlayer] & maskBoard[currentPlayer] & (oneMask << pos-8)){
            if(currentPlayer == Black){
                score+=6;
            }
            else{
                score+=10;
            }
        }
        else{
            score -=100;
        }
        if(board[currentPlayer] & maskBoard[currentPlayer] & (oneMask << pos+8)){
            if(currentPlayer == Black){
                score+=6;
            }
            else{
                score+=10;
            }
        }
        else{
            score -=100;
        }
        if(board[currentPlayer] & maskBoard[currentPlayer] & (oneMask << pos-9)){
            score+=2;
        }
        else{
            score -=50;
        }
        if(board[currentPlayer] & maskBoard[currentPlayer] & (oneMask << pos-7)){
            score+=2;
        }
        else{
            score -=50;
        }
        if(board[currentPlayer] & maskBoard[currentPlayer] & (oneMask << pos+9)){
            score+=2;
        }
        else{
            score -=50;
        }
        if(board[currentPlayer] & maskBoard[currentPlayer] & (oneMask << pos+7)){
            score+=2;
        }
        else{
            score -=50;
        }
    }
    
    if (hasWhiteWon()) return (turn == White)? 10000 : -10000;  
    if (hasBlackWon()) return (turn == Black)?  10000 : -10000;  

    return score;
}

std::vector<int> Board::generateAllLegalMoves() {
    std::vector<int> legalMoves;

    for (int position = 0; position < BOARD_SIZE; ++position) {
        if (isLegalMove(position)) { // Verifica si el movimiento es legal
            legalMoves.push_back(position); // Agrega a la lista de movimientos legales
        }
    }
    return legalMoves;
}

bool Board::endGame() {
    return hasWhiteWon() || hasBlackWon(); // Aquí puedes incluir condiciones de empate si aplica
}

