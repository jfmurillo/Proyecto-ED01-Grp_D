#include "../header/GameMenu.h"
#include "../header/KeyInput.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "../header/PlayerRecord.h"


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


    // logic de las keys
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

void GameMenu::newPlayerMenu() {
    std::cout << "=== Register a New Player ===" << std::endl;
        string nickname, name, lastName, email;
        int age;

        std::cout << "Enter nickname: ";
        std::cin >> nickname;
        std::cout << "Enter Name: ";
        std::cin >> name;
        std::cout << "Enter Last Name: ";
        std::cin >> lastName;
        std::cout << "Enter Email: ";
        std::cin >> email;
        std::cout << "Enter Age: ";
        std::cin >> age;

        Player newPlayer(nickname, name, lastName, email, age);
        record.registerPlayer(newPlayer);

        std::cout << "Player registered successfully!" << std::endl;
}

void GameMenu::existingPlayerMenu() {
    while (true) {
            std::cout << "=== Manage Existing Players ===" << std::endl;
            std::cout << "1. Show all players" << std::endl;
            std::cout << "2. Delete a player" << std::endl;
            std::cout << "3. Find a player by ID" << std::endl;
            std::cout << "0. Back to main menu" << std::endl;
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                    std::cout << "=== Player Record ===" << std::endl;
                    record.showPlayerRecord();
                    break;
                case 2: {
                    std::cout << "Enter player nickname to delete: ";
                    string nickname;
                    std::cin >> nickname;
                    if (record.deletePlayer(nickname)) {
                        std::cout << "Player deleted successfully." << std::endl;
                    } else {
                        std::cout << "Player not found." << std::endl;
                    }
                    break;
                }
                case 3: {
                    std::cout << "Enter player nickname to find: ";
                    string nickname;
                    std::cin >> nickname;
                    int index = record.findPlayerById(nickname);
                    if (index != -1) {
                        std::cout << "Player found at position " << index + 1 << "." << std::endl;
                    } else {
                        std::cout << "Player not found." << std::endl;
                    }
                    break;
                }
                case 0:
                    return; 
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
}

void GameMenu::showMenu() {
    while (true) {
            std::cout << "=== Main Menu ===" << std::endl;
            std::cout << "1. Register New Player" << std::endl;
            std::cout << "2. Manage Existing Players" << std::endl;
            std::cout << "0. Back" << std::endl;
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                    newPlayerMenu();
                    break;
                case 2:
                    existingPlayerMenu();
                    break;
                case 0:
                    std::cout << "Exiting program." << std::endl;
                    return;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
            }
        }
    };

void GameMenu::showGameMenu() {
    while (true) {
            std::cout << "=== Game Menu ===" << std::endl;
            std::cout << "1. Start Game" << std::endl;
            std::cout << "2. Player Menu" << std::endl;
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
                        showMenu();
                    }
                    break;
                case 2:
                    showMenu();
                    break;
                case 0:
                    exit();
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
}
