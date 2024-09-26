#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>
#include <bitset>
#include <vector>

typedef uint64_t U64;
enum MARK{White, Black};
const int N = 8;
const int BOARD_SIZE = 64;


const int DIRECTIONS[8][2] = {
    {1, 0},   // Derecha
    {-1, 0},  // Izquierda
    {0, 1},   // Abajo
    {0, -1},  // Arriba
    {1, 1},   // Diagonal derecha-abajo
    {1, -1},  // Diagonal derecha-arriba
    {-1, 1},  // Diagonal izquierda-abajo
    {-1, -1}  // Diagonal izquierda-arriba
};

class Board
{
    U64 board[2]{};
    U64 maskBoard[2]{};
    U64 oneMask{};
    U64 zeroMask{};
    MARK turn;

    U64 fullMask{};

    bool isLegalMove(int position); //Verificar si la pos es legal.
    bool isEating(int position);
    bool eatRigth(int position);
    bool eat(int position, int direction);
    bool isValidInLimits(int x, int y); // Verificar si el numero ingresado esta dentro de los limites
    bool existsWayDfs(MARK color, U64 map, U64& visit, int x, int y, int pf);

    public:
        Board(); //Constructor prototipe
        ~Board(); //Destructor prototipo
        bool makeMove(int position); // Permite mover
        void print(); // Imprime el tablero
        bool hasWhiteWon(); //Verifica si Blanco ha ganado
        bool hasBlackWon(); //Verifica si Negro ha ganado
        MARK getMark();//Retorna el turno
        int evaluateBoard(int depth);
        bool endGame();
        std::vector<int> generateAllLegalMoves();
};

#endif //BOARD_HPP
