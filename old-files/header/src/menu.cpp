// #include "Menu.h"

// Menu::Menu() : playerRecord() {}

// std::string Menu::getInput(const std::string& prompt) {
//     std::cout << prompt;
//     std::string input;
//     std::getline(std::cin, input);
//     return input;
// }

// void Menu::showMenu() {
//     while (true) {
//         std::cout << "1. New player" << std::endl;
//         std::cout << "2. Existing player" << std::endl;
//         std::cout << "Choose an option: ";
//         std::string choice = getInput("");
//         if (choice == "1") {
//             newPlayerMenu();
//         } else if (choice == "2") {
//             existingPlayerMenu();
//         } else {
//             std::cout << "Invalid input" << std::endl;
//         }
//     }
// }

// void Menu::newPlayerMenu() {
//     int playerID = std::stoi(getInput("Enter Player ID: "));
//     std::string name = getInput("Enter name: ");
//     std::string lastName = getInput("Enter last name: ");
//     std::string email = getInput("Email: ");
//     int age = std::stoi(getInput("Age: "));
//     Player newPlayer(playerID, name, lastName, email, age);
//     playerRecord.registerPlayer(newPlayer);
//     std::cout << "New player has been created" << std::endl;
// }


// void Menu::existingPlayerMenu() {
//     while (true) {
//         std::cout << "1. Show players" << std::endl;
//         std::cout << "2. Delete player" << std::endl;
//         std::cout << "3. Modify player" << std::endl;
//         std::cout << "4. Back to main menu" << std::endl;
//         std::cout << "Choose an option: ";
//         std::string choice = getInput("");
//         if (choice == "1") {
//             playerRecord.showPlayerRecord();
//         } else if (choice == "2") {
//             int playerID = std::stoi(getInput("Enter player ID to be deleted: "));
//             playerRecord.deletePlayer(playerID);
//             std::cout << "Player has been deleted." << std::endl;
//         } else if (choice == "3") {
//             int modifyID = std::stoi(getInput("Enter player ID to be modified: "));
//             modifyPlayer(modifyID);
//         } else if (choice == "4") {
//             return;
//         } else {
//             std::cout << "Invalid option" << std::endl;
//         }
//     }
// }


// void Menu::modifyPlayer(int playerID) {
//     auto& players = playerRecord.getPlayers();
//     for (auto& player : players) {
//         if (player.playerID == playerID) {
//             std::cout << "Modifying player ID " << playerID << std::endl;
//             player.name = getInput("New player name (current: " + player.name + "): ");
//             player.lastName = getInput("New last name (current: " + player.lastName + "): ");
//             player.email = getInput("New email (current: " + player.email + "): ");
//             player.age = std::stoi(getInput("New age (current: " + std::to_string(player.age) + "): "));
//             std::cout << "Player has been modified." << std::endl;
//             return;
//         }
//     }
//     std::cout << "Player not found." << std::endl;
// }
