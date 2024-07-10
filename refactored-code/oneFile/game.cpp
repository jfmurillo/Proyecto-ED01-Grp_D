#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <unordered_map>
#include <queue>
#include <windows.h>
using std::queue;
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

struct Node{
    string name;
    string sequence;
    Node* next;

    Node(const string& name, const string& sequence) : name(name), sequence(sequence), next(nullptr) {}
};

class Combo{
    private:
    Node* head;

    public:
    Combo(): head(nullptr){};

    void createCombo(const string name, const string sequence){
        Node* newNode = new Node(name, sequence);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        std::cout << "Combo '" << name << "' created using: " << sequence << std::endl;
    }

    string obtainSequence(const string& name) const {
        Node* current = head;
        while (current) {
            if (current->name == name) {
                return current->sequence;
            }
            current = current->next;
        }
        return "Combo not found.";
    }

    void executeCombo(const string& name) {
        Node* current = head;
        while (current) {
            if (current->name == name) {
                std::cout << "Combo '" << name << "' with sequence: " << current->sequence << std::endl;
                
                return;
            }
            current = current->next;
        }
        std::cout << "Combo '" << name << "' not found." << std::endl;
    }

    void removeCombo(const string& name) {
        if (!head) {
            std::cout << "Combo list is empty." << std::endl;
            return;
        }
        Node* current = head;
        Node* prev = nullptr;
        while (current) {
            if (current->name == name) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
                std::cout << "Combo '" << name << "' deleted." << std::endl;
                return;
            }
            prev = current;
            current = current->next;
        }
        std::cout << "Combo '" << name << "' not found." << std::endl;
    }

    void listCombos() const {
        if (!head) {
            std::cout << "No combos on combo list." << std::endl;
            return;
        }
        std::cout << "=== Combo List ===" << std::endl;
        Node* current = head;
        while (current) {
            std::cout << "Combo: " << current->name << ", Sequence: " << current->sequence << std::endl;
            current = current->next;
        }
    }

    string findCombo(const string& sequence) const {
        Node* current = head;
        while (current) {
            if (current->sequence == sequence) {
                return current->name;
            }
            current = current->next;
        }
        return "Combo with sequence '" + sequence + "' not found.";
    }

    ~Combo() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    void checkAndExecuteCombo(const string& inputSequence) {
        Node* current = head;
        while (current) {
            if (current->sequence == inputSequence) {
                std::cout << "Combo: " << current->name << ". executing..." << std::endl;
                executeCombo(current->name);
                return;
            }
            current = current->next;
        }
        std::cout << "Combo not find using sequence: " << inputSequence << std::endl;
    }
};

class KeyInput {
private:
    queue<char> keyQueue;
    Combo& comboManager;

public:
    KeyInput(Combo& comboMgr) : comboManager(comboMgr) {}

    void addKey(char key) {
        keyQueue.push(key);
        std::cout << "Key entered: " << key << std::endl;
    }

    string getCurrentSequence() const {
        string sequence;
        queue<char> tempQueue = keyQueue;
        while (!tempQueue.empty()) {
            sequence += tempQueue.front();
            tempQueue.pop();
        }
        return sequence;
    }

    char getFirstKeyPressed() {
        for (int key = 8; key <= 255; ++key) {
            if (GetAsyncKeyState(key) & 0x8000) {
                if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) {
                    return static_cast<char>(key);
                }
            }
        }
        return '\0';
    }

    void processInput() {
        char firstKey = getFirstKeyPressed();
        if (firstKey != '\0') {
            addKey(firstKey);
        }

        string currentSequence = getCurrentSequence();
        std::cout << "Actual sequence: " << currentSequence << std::endl;
        comboManager.checkAndExecuteCombo(currentSequence);
        clearKeys();
    }

    void clearKeys() {
        while (!keyQueue.empty()) {
            keyQueue.pop();
        }
    }
};


class GameMenu {
private:
    Timer time;
    PlayerRecord playerRecord;
    Combo comboManager;
    KeyInput keyInput;

public:
    GameMenu() : keyInput(comboManager) {}

    void showGameMenu() {
        char option;
        bool running = true;
        while (running) {
            std::cout << "====== Game Menu ======" << std::endl;
            std::cout << "1. Game Settings" << std::endl;
            std::cout << "2. Player settings" << std::endl;
            std::cout << "3. Combo settings" << std::endl;
            std::cout << "4. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> option;

            switch (option) {
                case '1':
                    gameSettings();
                    break;
                case '2':
                    playerSettings();
                    break;
                case '3':
                    comboSettings();
                    break;
                case '4':
                    std::cout << "Exiting game menu..." << std::endl;
                    running = false;
                    break;
                default:
                    std::cout << "Invalid option. Please try again." << std::endl;
                    break;
            }
        }
    }

    void playerSettings() {
        char option;
        while (true) {
            std::cout << "====== Player Settings ======" << std::endl;
            std::cout << "1. Register player" << std::endl;
            std::cout << "2. Delete player" << std::endl;
            std::cout << "3. Show player record" << std::endl;
            std::cout << "4. Back to main menu" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> option;

            switch (option) {
                case '1':
                    registerPlayer();
                    break;
                case '2':
                    deletePlayer();
                    break;
                case '3':
                    showPlayerRecord();
                    break;
                case '4':
                    return;
                default:
                    std::cout << "Invalid option. Please try again." << std::endl;
                    break;
            }
        }
    }

    void gameSettings(){
        char option;
        while (true) {
            std::cout << "====== Game Menu ======" << std::endl;
            std::cout << "1. Start Game" << std::endl;
            std::cout << "2. Training Mode" << std::endl;
            std::cout << "3. Back to main menu" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> option;

            switch (option) {
                case '1':
                    if (playerRecord.hasPlayers()){
                        start();
                    } else {
                        std::cout << "You need to register at least one player before starting the game." << std::endl;
                        playerSettings();
                    }
                    break;
                case '2':
                    trainingMode();
                    break;
                case '3':
                    return;
                default:
                    std::cout << "Invalid option. Please try again." << std::endl;
                    break;
            }
        }
    }

    void trainingMode() {
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

    void registerPlayer() {
        string nickname, name, lastName, email;
        int age;

        std::cout << "Enter nickname: ";
        std::cin >> nickname;
        std::cout << "Enter name: ";
        std::cin >> name;
        std::cout << "Enter last name: ";
        std::cin >> lastName;
        std::cout << "Enter email: ";
        std::cin >> email;
        std::cout << "Enter age: ";
        std::cin >> age;

        Player player(nickname, name, lastName, email, age);
        playerRecord.registerPlayer(player);
        std::cout << "Player registered successfully." << std::endl;
    }

    void deletePlayer() {
        string nickname;
        std::cout << "Enter player nickname to delete: ";
        std::cin >> nickname;
        if (playerRecord.deletePlayer(nickname)) {
            std::cout << "Player deleted successfully." << std::endl;
        } else {
            std::cout << "Player not found." << std::endl;
        }
    }

    void showPlayerRecord() const {
        playerRecord.showPlayerRecord();
    }

    void comboSettings() {
        char option;
        while (true) {
            std::cout << "====== Combo Settings ======" << std::endl;
            std::cout << "1. Create combo" << std::endl;
            std::cout << "2. Execute combo" << std::endl;
            std::cout << "3. Remove combo" << std::endl;
            std::cout << "4. List combos" << std::endl;
            std::cout << "5. Back to main menu" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> option;

            switch (option) {
                case '1':
                    createCombo();
                    break;
                case '2':
                    executeCombo();
                    break;
                case '3':
                    removeCombo();
                    break;
                case '4':
                    listCombos();
                    break;
                case '5':
                    return;
                default:
                    std::cout << "Invalid option. Please try again." << std::endl;
                    break;
            }
        }
    }

    void createCombo() {
        string name, sequence;
        std::cout << "Enter combo name: ";
        std::cin >> name;
        std::cout << "Enter combo sequence: ";
        std::cin >> sequence;
        comboManager.createCombo(name, sequence);
    }

    void executeCombo() {
        string name;
        std::cout << "Enter combo name to execute: ";
        std::cin >> name;
        comboManager.executeCombo(name);
    }

    void removeCombo() {
        string name;
        std::cout << "Enter combo name to remove: ";
        std::cin >> name;
        comboManager.removeCombo(name);
    }

    void listCombos() const {
        comboManager.listCombos();
    }

    void start() {
    std::cout << "=== Starting Game ===" << std::endl;
    std::cout << "Game started. Enjoy!" << std::endl;

    time.setTimeLimit(10);
    time.startTimer();
    std::cout << "Timer started: 1 minute from now. GO!" << std::endl;

    KeyInput keyInput(comboManager);
    char key = '\0';

    // while (!time.isTimeExceeded()) {
    //     firstKey = keyInput.getFirstKeyPressed();
    //     if (firstKey != '\0') {
    //         keyInput.addKey(firstKey);
    //         std::cout << "First key pressed: " << firstKey << std::endl;
    //     }
    //     keyInput.processInput();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // }

    while (!time.isTimeExceeded()) {
        std::cout << "Press a key: ";
        std::cin >> key;
        keyInput.addKey(key);
        keyInput.processInput();
    }

        time.stopTimer();
        std::cout << "Time limit exceeded!" << std::endl;
        std::cout << "Elapsed time: " << time.getElapsedTime() << " seconds" << std::endl;
    }

};




int main() {
    GameMenu gameMenu;
    gameMenu.showGameMenu();
    return 0;
}
