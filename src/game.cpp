#include <iostream>
#include <cstdint>
#include <chrono>
#include <thread>
#include <iostream>

#include "game.hpp"
#include "player.hpp"

Game::Game(){
    board = new Board();
    //iaPlayer = new Player();
}

Game::~Game() = default;

void Game::newBoard(){
    delete board;
    board = new Board();
}

void Game::loopGame(){
    
    int exit = 1;
    do
    {
        system("clear");
        setGameMode();
        bool hasonewin = false;
        while (!hasonewin)
        {
            int move;
            int abvalue = 0;
            std::chrono::duration<double> duration;

            switch (gameMode)
            {
            case PVP:
                if(board->getMark() == White){
                    std::cout << "Jugador de las blancas haga su movimiento" << std::endl;
                    std::cin >> move;
                }
                if(board->getMark() == Black){
                    std::cout << "Jugador de las negras haga su movimiento" << std::endl;
                    std::cin >> move;
                }   
                break;
            case PVE:
                if(board->getMark() == White){
                    std::cout << "Jugador de las blancas haga su movimiento" << std::endl;
                    std::cin >> move;
                }
                if(board->getMark() == Black){
                    std::cout << "Jugador de las negras haga su movimiento" << std::endl;
                    int bestPosition = -1;
                    auto start = std::chrono::high_resolution_clock::now();
                    abvalue = iaPlayer.negaScout(*board, 8, bestPosition, -10000000, 10000000);
                    move = bestPosition;
                    auto end = std::chrono::high_resolution_clock::now();
                    duration = end -start;
                }   
                break;
            case EVE:
                if(board->getMark() == White){
                    std::cout << "Juega blanco" << std::endl;
                    int bestPosition = -1;
                    move = iaPlayer.negaMax(*board, 0, bestPosition); 
                }
                if(board->getMark() == Black){
                    std::cout << "Juega negro" << std::endl;
                    int bestPosition = -1;
                    move = iaPlayer.negaMax(*board, 0, bestPosition);
                }   
                break;
            default:
                break;
            }
            board->makeMove(move);
            std::cout<<"Pensando"<< std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            
            

            //Pregunta Condicion de victoria
            system("clear");
            
            std::cout << "Tiempo de ejecución: " << duration.count() << " segundos" << std::endl;
            std::cout << "Puntaje Maximo: "<< iaPlayer.getScore() << std::endl;
            std::cout << "MD: "<< iaPlayer.getMD() << std::endl;
            std::cout << "Nodos Visitados: "<< iaPlayer.getNV() << std::endl;
            std::cout << "Iteraciones: "<< iaPlayer.getIT() << std::endl;
            iaPlayer.reset();
            board->print();
            hasonewin = hasOneWin();
        }
        std::cout<<"Desea salir?" << std::endl;
        std::cout<<"(1) Si" << std::endl;
        std::cout<<"(2) NO" << std::endl;
        std::cin >> exit;
                
        if(exit == 1){
            exit = 0;
        }
        else if(exit == 2){
            newBoard();
            system("clear");
        }
        
    } while (exit != 0);
        
}

bool Game::hasOneWin(){
    if(board->hasWhiteWon()){
        std::cout<< "Ha ganado el jugador de las blancas" << std::endl;
        return true;
    }
    else if(board->hasBlackWon()){
        std::cout<< "Ha ganado jugador de las negras" << std::endl;
        return true;
    }
    std::cout<< "Nadie ha Ganado" << std::endl;
    return false;
}

void Game::setGameMode(){
    
    int select = -1;
    while ((select < 1 || select > 3))
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        system("clear");
        std::cout << "Escoja modo de Juego" << std::endl;
        std::cout << "(1) Jugador vs IA" << std::endl;
        std::cout << "(2) Jugador vs Jugador" << std::endl;
        std::cout << "(3) IA vs IA" << std::endl;
        std::cin >> select;

        switch (select)
        {
        case 1:
            gameMode = PVE;
            std::cout<< "PVE" <<std::endl;
            break;
        case 2:
            gameMode = PVP;
            std::cout<< "PVP" <<std::endl;
            break;
        case 3:
            gameMode = EVE;
            std::cout<< "EVE" <<std::endl;
        default:
            std::cout<< "Ingrese una opción válida" <<std::endl;
            break;
        }
    }
}

//Intro
void Game::enterGame(){
    std::cout << " ⣿⣿⣿⣿⣿⣿ ⣿⣿⣿⣿⣿⣿ ⣿⣿⣿⣿⣿⣿ ⣿⣿    ⣿⣿"<< std::endl;
    std::cout << "   ⣿⣿   ⣿⣿  ⣿⣿ ⣿⣿  ⣿⣿ ⣿⣿    ⣿⣿"<< std::endl;
    std::cout << "   ⣿⣿   ⣿⣿⣿⣿⣿  ⣿⣿  ⣿⣿ ⣿⣿    ⣿⣿ "<< std::endl;
    std::cout << "   ⣿⣿   ⣿⣿   ⣿ ⣿⣿⣿⣿⣿⣿ ⣿⣿⣿⣿⣿ ⣿⣿⣿⣿⣿"<< std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
}

//Salida
void Game::exitGame(){
    std::cout << "Saliendo de Troll"<< std::endl;
}
