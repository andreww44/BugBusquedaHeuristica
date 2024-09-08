#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cstdint>

typedef uint64_t U64;

class Board {
private:
    //Miembros de datos privados (no accesibles fuera de la clase)

    uint64_t bBoard;
    uint64_t wBoard;

    void printBits(uint64_t value) const {
        // Utiliza std::bitset para convertir el valor en una cadena de bits
        std::bitset<64> bits(value);

        // Imprime la cadena de bits en grupos de 8 bits para mejor legibilidad
        for (int i = 0; i < 64; i += 8) {
            std::cout << bits.to_string().substr(i, 8) << std::endl;
        }
        std::cout << std::endl;
    }

public:
    // Constructor de la clase
    Board(uint64_t _wBoard = 0, uint64_t _bBoard = 0) : wBoard(_wBoard), bBoard(_bBoard){

    }

    // Método para Insertar una nueva pieza al tablero
    void insertPiece(){
        //Colocar las piezas van de izquierda a derecha
    }

    //Imprime el tablero 
    void printBoard(){
        printBits(wBoard);
    }
    
    //Retorna si la posicion del tablero es esta libre
    bool validMove(){
        // = tablero(numero a revisar << cuantas posiciones)
        //bool freepos = !(table& (1 << a-1));
        
        return true;
    }

};

//Funcion que imprime ambos tableros
int main()
{
    
    //FF00000000000000FF
    U64 whiteFile = 0xff000000000000ffULL; //Movimientos 
    U64 blackFile = 0x8181818181818181ULL;
   
    Board tablero(whiteFile, blackFile);
    
    tablero.printBoard();
   
    return 0;
}