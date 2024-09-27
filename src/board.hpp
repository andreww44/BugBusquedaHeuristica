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

    U64 winingBoard[2]{};

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
        MARK getActiveTurn() const;
        U64 getWhiteBoard() const;
        U64 getBlackBoard() const;
        
        int evaluateBoard(int depth);
        bool endGame();
        std::vector<int> generateAllLegalMoves();
        
        bool operator==(const Board &other) const {
            return turn==other.turn && board[Black]==other.board[Black] && board[White]==other.board[White];
        }
};

struct BoardHash
{
    std::size_t operator()(Board const& board) const noexcept
    {
        std::size_t h1 = std::hash<uint64_t>{}(board.getWhiteBoard());
        std::size_t h2 = std::hash<uint64_t>{}(board.getBlackBoard());
        std::size_t h3 = std::hash<bool>{}(board.getActiveTurn() == Black);

        // Mezclar usando XOR y desplazamientos
        return h1 ^ (h2 << 1) ^ (h2 >> 1) ^ (h3 << 2) ^ (h3 >> 2);
    }
};

#endif //BOARD_HPP
