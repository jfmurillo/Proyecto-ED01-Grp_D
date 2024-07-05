#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>
#include <chrono>
#include <thread>
#include <cstdlib>
using std::list;
using std::string;
using std::vector;

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::chrono::time_point<std::chrono::steady_clock> endTime;
    int timeLimitSeconds;
    bool running;

public:
    Timer() : timeLimitSeconds(0), running(false) {}

    void setTimeLimit(int seconds) {
        timeLimitSeconds = seconds;
    }

    void startTimer() {
        startTime = std::chrono::steady_clock::now();
        running = true;
    }

    void stopTimer() {
        endTime = std::chrono::steady_clock::now();
        running = false;
    }

    bool isTimeExceeded() {
        if (running) {
            auto currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsedSeconds = currentTime - startTime;
            return elapsedSeconds.count() > timeLimitSeconds;
        } else {
            std::chrono::duration<double> elapsedSeconds = endTime - startTime;
            return elapsedSeconds.count() > timeLimitSeconds;
        }
    }

    double getElapsedTime() const {
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedSeconds = currentTime - startTime;
        return elapsedSeconds.count();
    }
};

class Player {
private:
    string nickname;
    string name;
    string lastName;
    string email;
    int age;

public:
    Player(string nickname, string name, string lastName, string email, int age)
        : nickname(nickname), name(name), lastName(lastName), email(email), age(age) {}

    string getNickName() const { return nickname; }
    string getName() const { return name; }
    string getLastName() const { return lastName; }
    string getEmail() const { return email; }
    int getAge() const { return age; }

    void setName(const string &name) { this->name = name; }
    void setLastName(const string &lastName) { this->lastName = lastName; }
    void setEmail(const string &email) { this->email = email; }
    void setAge(int age) { this->age = age; }

    void displayPlayer() const {
        std::cout << "ID: " << nickname << ", Name: " << name << ", Last Name: " << lastName
                  << ", Email: " << email << ", Age: " << age << std::endl;
    }

    Player getPlayerbyID(string nickname) {
        std::cout << "Please enter player nickname: ";
        return *this;
    }

    Player modifyPlayer(string nickname) {
        return *this;
    }
};

class PlayerRecord {
private:
    list<Player> players;

public:
    void registerPlayer(const Player player) {
        players.push_back(player);
    }

    bool deletePlayer(string nickname) {
        for (auto i = players.begin(); i != players.end(); ++i) {
            if (i->getNickName() == nickname) {
                players.erase(i);
                return true;
            }
        }
        std::cout << "Player not found" << std::endl;
        return false;
    }

    void showPlayerRecord() const {
        if (players.empty()) {
            std::cout << "No players registered." << std::endl;
            return;
        }
        for (const auto &player : players) {
            player.displayPlayer();
        }
    }

    int findPlayerById(string nickname) const {
        auto i = std::find_if(players.begin(), players.end(), [nickname](const Player &player) {
            return player.getNickName() == nickname;
        });

        if (i != players.end()) {
            return std::distance(players.begin(), i);
        }
        std::cout << "Not found" << std::endl;
        return -1;
    }

    bool hasPlayers() const {
        return !players.empty();
    }
};

class GameMenu;

class Menu {
private:
    PlayerRecord record;
    GameMenu* gameMenu;

public:
    Menu(GameMenu* gm) : gameMenu(gm) {}

    void newPlayerMenu() {
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

    void existingPlayerMenu() {
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

    void showMenu() {
        while (true) {
            std::cout << "=== Main Menu ===" << std::endl;
            std::cout << "1. Register New Player" << std::endl;
            std::cout << "2. Manage Existing Players" << std::endl;
            std::cout << "3. Go to Game Menu" << std::endl;
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
                case 3:
                    if (gameMenu) {
                        gameMenu->showGameMenu();
                    }
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
};

class GameMenu {
private:
    Timer time;
    PlayerRecord record;
    Menu mainMenu;

public:
    GameMenu() : mainMenu(this) {}

    void start() {
        std::cout << "=== Starting Game ===" << std::endl;
        std::cout << "Game started. Enjoy!" << std::endl;

        time.setTimeLimit(125);
        time.startTimer();
        std::cout << "Timer started: 2 minutes from now. GO!" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(126));
        if (time.isTimeExceeded()) {
            std::cout << "Time limit exceeded!" << std::endl;
        }

        time.stopTimer();

        std::cout << "Elapsed time: " << time.getElapsedTime() << " seconds" << std::endl;

        // falta el key input para las teclas y que vaya saliendo los combos que hace
    }

    void trainingMode() {
        std::cout << "=== Training Mode ===" << std::endl;
        std::cout << "Training mode activated." << std::endl;
        // aqui se puede implementar algún comando para salir del modo training
        // y que vuelva al menu del juego
    }

    void exit() {
        std::cout << "Exiting the game menu." << std::endl;
        // aqui se deberia de volver al menu?, idk
        std::exit(0);
    }

    void showGameMenu() {
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
                        mainMenu.showMenu();
                    }
                    break;
                case 2:
                    if (record.hasPlayers()) {
                        trainingMode();
                    } else {
                        std::cout << "You need to register at least one player before entering training mode." << std::endl;
                        mainMenu.showMenu();
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
};

int main() {
    GameMenu gameMenu;
    gameMenu.showGameMenu();
    return 0;
}
