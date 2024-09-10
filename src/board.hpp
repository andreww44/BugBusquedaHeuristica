#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>

typedef uint64_t U64;
enum MARK{White, Black};
const int N = 8;
const int BOARD_SIZE = 64;

class Board
{
    U64 board[2];
    U64 maskBoard[2];
    U64 oneMask;
    U64 zeroMask;
    MARK turn;

    bool isLegalMove(int position); //Verificar si la pos es legal.
    bool isValidInLimits(int x, int y); // Verificar si el numero ingresado esta dentro de los limites
    bool existsWayDfs(MARK color, U64 map, U64& visit, int x, int y, int pf);

    public:
        Board(); //Constructor prototipe
        ~Board(); //Destructor prototipo
        bool makeMove(int position); // Permite mover
        void print(); // Imprime el tablero
        bool hasWhiteWon(); //Verifica si Blanco ha ganado
        bool hasBlackWon(); //Verifica si Negro ha ganado
};

#endif //BOARD_HPP
