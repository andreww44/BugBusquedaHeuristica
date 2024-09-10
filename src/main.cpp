#include <iostream>
#include <string>
#include <vector>
#include <bitset>

#include "board.hpp"

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
    

    tablero.print();
   
    if(tablero.hasWhiteWon()){
        std::cout << "White has won" << std::endl;
    } else if(tablero.hasBlackWon()){
        std::cout << "Black has won" << std::endl;
    } else {
        std::cout << "Nadie ha ganado" << std::endl;
    }
    return 0;
}