#include <iostream>
#include <cstdint>
#include <chrono>
#include <thread>

#include "game.hpp"
#include "player.hpp"

Game::Game(){
    board = new Board();
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
        setPlayers();
        bool hasonewin = false;
        while (!hasonewin)
        {
            switch (gameMode)
            {
            case PVP:
                int move;
                if(board->getMark() == White){
                    std::cout << "Jugador de las blancas haga su movimiento" << std::endl;
                    std::cin >> move;
                }
                if(board->getMark() == Black){
                    std::cout << "Jugador de las negras haga su movimiento" << std::endl;
                    std::cin >> move;
                }   
                board->makeMove(move);
                std::cout<<"Pensando"<< std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                
                //Pregunta Condicion de victoria
                system("clear");
                hasonewin = hasOneWin();
                board->print();
                break;
            case PVE:
                hasonewin = true;
                break;
            case EVE:
                hasonewin = true;
                break;
            default:
                break;
            }
        }
        std::cout<<"Desea salir?" << std::endl;
        std::cout<<"(1) Si" << std::endl;
        std::cout<<"(2) NO" << std::endl;
        std::cin >> exit;
                
        if(exit == 1){
            std::cout<< "Saliendo" << std::endl;
            exit = 0;
        }
        else if(exit == 2){
            std::cout << "Volviendo a jugar" << std::endl;
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

void Game::setPlayers(){
    
    int select = -1;
    while (select != (1 || 2 || 3))
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
            system("clear");
            std::cout<< "PVE" <<std::endl;
            break;
        case 2:
            gameMode = PVP;
            system("clear");
            std::cout<< "PVP" <<std::endl;
            select = 1;
            break;
        case 3:
            gameMode = EVE;
            std::cout<< "En progreso" <<std::endl;
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
//Setea el modo de juego
void Game::setGameMode(GameMode gM){
    gameMode = gM;
}