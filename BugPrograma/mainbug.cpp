#include <iostream>
#include <string>

const int SIZE = 3; // Tamaño del tablero hexagonal

void printHexBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        std::cout << std::string(SIZE - i - 1, ' '); // Espaciado para la forma hexagonal
        for (int j = 0; j < SIZE; ++j) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    for (int i = 1; i < SIZE; ++i) {
        std::cout << std::string(i, ' '); // Espaciado para la forma hexagonal
        for (int j = 0; j < SIZE; ++j) {
            std::cout << board[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {
    char board[SIZE][SIZE] = { 
        {'B', '.', '.'}, 
        {'.', 'B', '.'}, 
        {'.', '.', 'B'} 
    };
    printHexBoard(board);
    return 0;
}