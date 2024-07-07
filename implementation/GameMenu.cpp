#include "../header/GameMenu.h"
#include "../header/Menu.h"
#include "../header/KeyInput.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "../header/PlayerRecord.h"

GameMenu::GameMenu() : mainMenu(nullptr) {
    mainMenu = new Menu(record, *this);
}

GameMenu::~GameMenu() {
    delete mainMenu;
}

// todo: revisar esto
//void GameMenu::start() {
//    mainMenu->showMenu();
//}

void GameMenu::start() {
    std::cout << "=== Starting Game ===" << std::endl;
    std::cout << "Game started. Enjoy!" << std::endl;

    time.setTimeLimit(125);
    time.startTimer();
    std::cout << "Timer started: 2 minutes from now. GO!" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(126));
    if (time.isTimeExceeded()) {
        std::cout << "Time limit exceeded!" << std::endl;
    }


    // logica de las teclas
    time.stopTimer();

    std::cout << "Elapsed time: " << time.getElapsedTime() << " seconds" << std::endl;
}

void GameMenu::trainingMode() {
    std::cout << "=== Training Mode ===" << std::endl;
    std::cout << "Training mode activated." << std::endl;
    KeyInput keyInput(comboManager);

    while (true) {
        std::cout << "Enter key (press 'x' to exit training mode): ";
        char key;
        std::cin >> key;

        if (key == 'x' || key == 'X') {
            break;
        }

        keyInput.addKey(key);
        keyInput.processInput();
    }

    std::cout << "Training mode ended." << std::endl;
}

void GameMenu::exit() {
    std::cout << "Exiting the game menu." << std::endl;
    std::exit(0);
}

void GameMenu::showGameMenu() {
    while (true) {
        std::cout << "=== Game Menu ===" << std::endl;
        std::cout << "1. Start Game" << std::endl;
        std::cout << "2. Training Mode" << std::endl;
        std::cout << "3. Player Menu" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (record.hasPlayers()) {
                    start();
                } else {
                    std::cout << "You need to register at least one player before starting the game." << std::endl;
                    mainMenu->showMenu();
                }
                break;
            case 2:
                if (record.hasPlayers()) {
                    trainingMode();
                } else {
                    std::cout << "You need to register at least one player before entering training mode." << std::endl;
                    mainMenu->showMenu();
                }
                break;
            case 3:
                mainMenu.showMenu();
                break;
            case 0:
                exit();
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}
