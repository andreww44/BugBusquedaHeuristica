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
    
    bool exit = false;
    
        setPlayers();
        int flag = 1;
        while (flag)
        {
            //flag = 0;
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
                if(move != 0){
                    board->makeMove(move);
                    if(!board->makeMove(move)){
                        std::cout << "Ingrese un valor válido" << std::endl;
                    }
                }
                system("clear");
                board->print();
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
            case PVE:
                //std::
                flag = 0;
                break;
            case EVE:
                flag = 0;
                break;
            default:
                break;
            }
        }
}

void Game::setPlayers(){
    
    int select = -1;
    while (select != (1 || 2))
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

void Game::enterGame(){
    std::cout << "Entrando a Troll"<< std::endl;
    std::cout << " ⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀"<< std::endl;
    std::cout << " ⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀ "<< std::endl;
    std::cout << "    ⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆" << std::endl;
    std::cout << "       ⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀"<< std::endl;
    std::cout << "    ⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆" <<std::endl;
    std::cout << "  ⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿ " << std::endl;
    std::cout << " ⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉"<<std::endl;
    std::cout << " ⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇" << std::endl;
    std::cout << " ⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇" << std::endl;
    std::cout << "       ⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇" << std::endl;
    std::cout << "        ⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿ "<<std::endl;
    std::cout << "     ⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇" << std::endl;
    std::cout << "     ⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃" << std::endl;
    std::cout << "      ⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁" << std::endl;
    std::cout << "        ⠉⠛⠻⠿⠿⠿⠿⠛⠉" << std::endl;
}

void Game::exitGame(){
    std::cout << "Saliendo de Troll"<< std::endl;

}

void Game::setGameMode(GameMode gM){
    gameMode = gM;
}