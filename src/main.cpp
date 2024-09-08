#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cstdint>

typedef uint64_t U64;
enum MARK{White, Black};

class Board {
private:
    //Miembros de datos privados (no accesibles fuera de la clase)

    U64 board[2];
    U64 maskBoard[2];
    U64 oneMask;
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
    }

    // Metodo que permite el hacer un movimiento.
    bool makeMove(int position){
        if(isLegalMove(position)){
            board[turn] |= (oneMask << position);
            turn = 1-turn == 0 ? White : Black;
            return true;
        }
        return false;
    }

    //Imprime el tablero 
    void print(){

        U64 wTable = board[White] & maskBoard[White];
        U64 bTable = board[Black] & maskBoard[Black];

        //U64 table = wTable | bTable; 
        std::cout << "Tablero Troll" << std::endl;
        for (int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++){
                if(wTable&(oneMask << (j+ (i*8)))){
                    std::cout<<"W ";
                }
                else if(bTable&(oneMask << (j+ (i*8)))){
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
};

//Funcion que imprime ambos tableros
int main()
{
    Board tablero;
    
    tablero.makeMove(2);
    tablero.makeMove(24);
    tablero.makeMove(25);
    tablero.makeMove(1);

    tablero.print();
   
    return 0;
}