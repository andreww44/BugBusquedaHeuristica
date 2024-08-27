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
void fillHexBoard(std::vector<Hex>& board) {
    
    for (int index = 0; index < board.size(); index++) {
        board[index].q = _cq[index];
        board[index].r = _cr[index];
        board[index].s = _cs[index];   
    }
}

void printTableBug(int w){
    
    //char none = ;
    int it = 2*w -1;
    for (int i = 0; i < it; i++)
    {
        for(int j = 0; j < it; j++)
        {
            if(i == 0 || i == it-1){
                if(j== 0 || j == 1){
                    std::cout << " ";
                }
                else{
                    std::cout << "* ";
                }
            }
            if(i == 1 || i == it-2){
                if(j== 0){
                    std::cout << " ";
                }
                else{
                    std::cout << "* ";
                }
            }
            if(i == 2){
                std::cout << "* ";
            }
            
        }
        std::cout << "\n";
    }
    
    //std::cout << it << "\n";

}

int main() {
    int width = 3;
    
    std::cout<<"Tamaño del tablero de 3x3x3x3x3 - Bug\n";
    
    int size = 3 * width * (width - 1)+1;

    std::vector<Hex> board(size);

    std::cout << board.size() << + "\n";
    // Inicializa el tablero

    fillHexBoard(board);

    // Imprimir las coordenadas de las piezas
    for (int i = 0; i < size; i++) {
        std::cout << "Pieza " << i << ": (" 
                  << board[i].q << ", " 
                  << board[i].r << ", " 
                  << board[i].s << ")\n";
    }

    printTableBug(width);

    return 0;
}