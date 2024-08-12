#include "../header/Menu.h"
#include "../header/GameMenu.h"
#include <iostream>

Menu::Menu(PlayerRecord& record, GameMenu& gameMenu)
    : record(record), gameMenu(gameMenu) {}

void Menu::newPlayerMenu() {
    std::cout << "=== Register a New Player ===" << std::endl;
    std::string nickname, name, lastName, email;
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
    gameMenu.showGameMenu();
    
}

void Menu::existingPlayerMenu() {
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
            std::string nickname;
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
            std::string nickname;
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

void Menu::showMenu() {
    while (true) {
        std::cout << "=== Main Menu ===" << std::endl;
        std::cout << "1. Register New Player" << std::endl;
        std::cout << "2. Manage Existing Players" << std::endl;
        std::cout << "0. Exit" << std::endl;
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
}
