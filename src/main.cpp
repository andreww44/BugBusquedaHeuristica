#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cstdint>

typedef uint64_t U64;
enum MARK{White, Black};
const int N = 8;

class Board {
private:
    //Miembros de datos privados (no accesibles fuera de la clase)

    U64 board[2];
    U64 maskBoard[2];
    U64 oneMask;
    U64 zeroMask;
    MARK turn;
   
    //Retorna si la posicion del tablero es esta libre
    bool isLegalMove(int position){
        //std::cout << "Wb" << std::bitset<64>(wBoard) << std::endl;
        if(position < 0 || position > 64)
            return false;
        if (turn == White && ( (board[White] |(board[Black] & maskBoard[Black])) & (oneMask << position) ))          
            return false;
        if (turn == Black && ( (board[Black] |(board[White] & maskBoard[White])) & (oneMask << position) ))
            return false;
        return true;
    }

public:
    //Destructor Prototype
    ~Board() = default;

    // Constructor de la clase
    Board(){
        board[White] = 0x8181818181818181ULL;
        board[Black] = 0xff000000000000ffULL;
        maskBoard[White] = ~board[White];
        maskBoard[Black] = ~board[Black];
        turn = White;
        oneMask = 1ULL;
        zeroMask = 0ULL;
    }

    // Metodo que permite el hacer un movimiento.
    bool makeMove(int position){
        if (position < 0 || position >= BOARD_SIZE) {
    std::cerr << "Error: Position fuera de rango." << std::endl;
    return false;
    }
        else if(isLegalMove(position)){
            board[turn] |= (oneMask << position);
            turn = (turn == White) ? Black : White;
            return true;
        }
        turn = (turn == White) ? Black : White;
        return false;
    }

    //Imprime el tablero 
    void print(){

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

    bool hasWonWhite(){
        U64 map = board[White] & maskBoard[White];
        U64 visit = zeroMask;
        for(int i = 0; i < N; i++){
            if(existsWaydfs(White, map, visit, i,0,7)){
                return true;
            }
        }
        return false;       
    }
    
    bool hasWonBlack(){
        U64 map = board[Black] & maskBoard[Black];
        U64 visit = zeroMask;
        for(int i = 0; i < N; i++){
            if(existsWaydfs(Black, map, visit, 0,i,7)){
                return true;
            }
        }
        return false; 
    }

    bool isValidInLimits(int x, int y){
        return x >= 0 && x < N && y >=0 && y < N;
    }

    bool existsWaydfs(MARK color, U64 map, U64& visit, int x, int y, int pf){

        if(!isValidInLimits(x, y)){
            return false;
        }

        int posicion = x*N + y;

        if((visit && (oneMask << posicion )) || !(map &(oneMask << posicion))){
            return false;
        }

        visit |= (oneMask << posicion);

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
        if(y + 1 < N && existsWaydfs(color, map, visit, x, y+1, pf)){
            return true;
        }

        // Revisa Arriba
        if(x-1 >= 0 && existsWaydfs(color, map, visit, x-1, y, pf)){
            return true;
        }

        // Revisa hacia abajo
        if(x + 1 < N && existsWaydfs(color, map, visit, x + 1, y, pf)){
            return true;
        }

        //Revisa Izquierda

        if(y - 1 >= 0 && existsWaydfs(color, map, visit, x, y-1, pf)){
            return true;
        }        
        return false;
    }
};

//Funcion que imprime ambos tableros
int main()
{
    Board tablero;
    
    tablero.makeMove(2); //1
    tablero.makeMove(8);

    tablero.makeMove(10); //2 
    tablero.makeMove(17);
    
    tablero.makeMove(18); //3
    tablero.makeMove(25);
    
    tablero.makeMove(26); //4
    tablero.makeMove(33); 
    
    tablero.makeMove(34); //5
    tablero.makeMove(41);  
    
    tablero.makeMove(42); //6
    tablero.makeMove(49); 
    
    tablero.makeMove(50); //7
    tablero.makeMove(57);
    
    tablero.makeMove(58); //8
    tablero.makeMove(57); 

    //tablero.makeMove(58); //8
    //tablero.makeMove(24); 
    

    tablero.print();
   
    if(tablero.hasWonWhite()){
        std::cout << "White has won" << std::endl;
    } else if(tablero.hasWonBlack()){
        std::cout << "Black has won" << std::endl;
    } else {
        std::cout << "Nadie ha ganado" << std::endl;
    }
    return 0;
}