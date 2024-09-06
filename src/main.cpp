#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cstdint>

//Coordenadas para cada punto del tablero
unsigned int w_table = 0x0000000;
unsigned int b_table = 0x0000000;
unsigned int table = 0x0;

class Board {
private:
    //Miembros de datos privados (no accesibles fuera de la clase)

    uint64_t bBoard;
    uint64_t wBoard;

public:
    // Constructor de la clase
    Board(uint64_t _bBoard, uint64_t _wBoard){
        bBoard = _bBoard;
        wBoard = _wBoard;
    }

    // Método para Insertar una nueva pieza al tablero
    void insertPiece(){

    }

    //Imprime el tablero 
    void printBoard(){
        std::cout << "Imprimir";
    }
    
    //Retorna si la posicion del tablero es esta libre
    bool validMove(){
        // = tablero(numero a revisar << cuantas posiciones)
        //bool freepos = !(table& (1 << a-1));
        
        return true;
    }



};

//Funcion que imprime ambos tableros
void printBoard(){
    int count = 1;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if(i == 0){
                if(j == 0 || j == 1){
                    std::cout << " ";
                }
                else if(w_table& (1 << j-2))
                {
                    std::cout << "W ";
                }
                else if(b_table&(1<<j-2)){
                    std::cout << "B ";
                }
                else{
                    std::cout << "* ";
                }
            }
            if(i== 1){
                if(j == 0){
                    std::cout << " ";
                }
                else if(w_table& (1 << j+2))
                {
                    std::cout << "W ";
                }
                else if(b_table&(1<<j+2)){
                    std::cout << "B ";
                }
                else{
                    std::cout << "* ";
                }
            }
            if(i == 2){
                if(w_table& (1 << j+7)){
                    std::cout << "W ";
                }
                else if(b_table& (1 << j+7))
                {
                    std::cout << "B ";
                }
                else{
                    std::cout << "* ";
                }
            }
            if(i == 3){
                if(j == 0){
                    std::cout << " ";
                }
                else if(w_table& (1 << j+11))
                {
                    std::cout << "W ";
                }
                else if(b_table& (1 << j+11)){
                    std::cout << "B ";
                }
                else{
                    std::cout << "* ";
                }
            }
            if(i == 4){
                if(j == 0 || j == 1){
                    std::cout << " ";
                }
                else if(w_table& (1 << j+14))
                {
                    std::cout << "W ";
                }
                else if(b_table& (1 << j+14))
                {
                    std::cout << "B ";
                }
                else{
                    std::cout << "* ";
                }
            }
        }
        std::cout << "\n";
    }
}

int main()
{
   

    /*
    int a = -1;
    int jugador = 0;
    unsigned int up = 0x0;

    std::cout << "Bienvenido a Bug" << std::endl;
    while (a != 0)
    {
        if(jugador == 0){
            std::cout << "JUEGA NEGRO" << std::endl;
        }
        else{
            std::cout << "JUEGA BLANCA" << std::endl;
        }
        std::cout << "Ingrese en que posicion del 1 al 19 quiere ingresar a la ficha" << std::endl;
        std::cout << "Ingrese 0 para salir" << std::endl;
        std::cin >> a;

        unsigned int newPiece = 0x0000001;
        newPiece = 1 << a-1;

        bool freepos = !(table& (1 << a-1));
            //w_table& (1 << j-2)
        if(a!=0 && freepos){
            if(jugador == 0){
                b_table = b_table | newPiece;
                jugador = 1;
            }
            else{
                w_table = w_table | newPiece;
                jugador = 0;
            }
            table = table | newPiece;
            printBoard();
        }
        else{
            std::cout << "INGRESE POSICION VALIDA" << std::endl;
        }
    }
    
    std::cout << "Saliendo" << std::endl;*/
    return 0;
}