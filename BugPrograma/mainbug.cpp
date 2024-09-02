#include <iostream>
#include <string>
#include <vector>
#include <bitset>

//Coordenadas para cada punto del tablero
unsigned int w_table = 0x0000000;
unsigned int b_table = 0x0000000;

//Funcion que imprime ambos tableros
void printBoard(){
    int count = 1;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if(i == 0){
                if(j == 0 || j == 1){
                    std::cout << " ";
                }
                else if(w_table& (1 << j+14))
                {
                    std::cout << "W ";
                }
                else if(b_table&(1<<j+14)){
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
                else if(w_table& (1 << j+11))
                {
                    std::cout << "W ";
                }
                else if(b_table&(1<<j+11)){
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
                else if(w_table& (1 << j+2))
                {
                    std::cout << "W ";
                }
                else if(b_table& (1 << j+2)){
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
                else if(w_table& (1 << j-2))
                {
                    std::cout << "W ";
                }
                else if(b_table& (1 << j-2))
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
    unsigned int hexValue = 0x02;
    //Valor Maximo para el enmascaramiento
    unsigned int hexMax = 0x0007FFFF;
    //Tablero de las blancas
    unsigned int hexWhite = 0x0;
    //Tablero de las negras
    unsigned int hexBlack = 0x0;
    /*
    std::cout << "Valor Hexadecimal = " << std::hex << table << std::endl;
    std::bitset<32> bits(table);
    std::cout << "Valor en bits = " << bits << std::endl;
    //Tablero 
    std::cout << "Valor Hexadecimal Maximo = " << std::hex <<hexMax << std::endl;
    std::bitset<32> blackbits(hexMax);
    std::cout << "Valor en Bits Maximo = " << blackbits << std::endl;
*/
    //Ciclo de juego
    
    int a = -1;

    unsigned int up = 0x0;
    while (a != 0)
    {
        std::cout << "Bienvenido a Bug" << std::endl;
        std::cout << "Ingrese en que posicion del 1 al 19 quiere ingresar a la ficha" << std::endl;
        std::cout << "Ingrese 0 para salir" << std::endl;
        std::cin >> a;

        unsigned int newPiece = 0x0000001;

        newPiece = 1 << a-1;

        std::bitset<32> bits(newPiece);
        std::cout << "Valor en bits = " << bits << std::endl;
        
        if(a!=0){
            up = newPiece;
            w_table = w_table | up;
            printBoard();
        }
    }
    
    w_table = up;
    printBoard();
    
    return 0;
}