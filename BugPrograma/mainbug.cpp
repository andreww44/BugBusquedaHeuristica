#include <iostream>
#include <string>
#include <vector>

//Coordenadas para cada punto del tablero
int _cq[19] = {0,1,2,-1,0,1,2,-2,-1,0,1,2,-2,-1,0,1,-2,-1,0};
int _cr[19] = {-2,-2,-2,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,2,2,2}; 
int _cs[19] = {2,1,0,2,1,0,-1,2,1,0,-1,-2,1,0,-1,-2,0,-1,-2}; 

// Define el tamaño del tablero
//Formula para estimar el tamaño del tablero. 3n(n−1)+1
//const int WIDTH = 3; // Ancho del tablero

//Estructura que guarda las coordenas axiales de cada punto
struct Hex {
    int q; // Coordenada xial Q
    int r; // Coordenada Axial R
    int s; // Coordenada Axial S
    bool occupied; // Estado del hexágono (por ejemplo, si está ocupado o no)
};


//En proceso función para llenar con las coordenadas de cada pieza correspondiente.
void fillHexBoard(std::vector<Hex>& piezas, int radio) {
    
    int index = 0;
    
    // Primer hexágono en el centro
    piezas[index++] = {0, 0, 0, false};

    // Llenar los hexágonos en anillos alrededor del centro
    for (int r = 1; r <= radio; ++r) {
        int q = -r;
        int s = 0;
        int temp_r = r;
    }
}

int main() {
    int width = 3;
    
    std::cout<<"Tamaño del tablero de 3x3x3x3x3   -   Bug Gameplay\n";
    
    int size = 3 * width * (width - 1)+1;

    std::vector<Hex> board(size);

    std::cout << board.size() << + "\n";
    // Inicializa el tablero

    fillHexBoard(board, width);

    int i = 0;
    /*/ Imprimir las coordenadas de las piezas
    for (i = 0; i < size; ++i) {
        std::cout << "Pieza " << i << ": (" 
                  << board[i].q << ", " 
                  << board[i].r << ", " 
                  << board[i].s << ")\n";
    }*/

    std::cout << i << "\n";

    return 0;
}