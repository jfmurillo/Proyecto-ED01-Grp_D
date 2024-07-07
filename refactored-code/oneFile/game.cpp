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

class KeyInput{
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

    void processInput() {
        string currentSequence = getCurrentSequence();
        std::cout << "Actual sequence: " << currentSequence << std::endl;
        comboManager.checkAndExecuteCombo(currentSequence);
        while (!keyQueue.empty()){
            keyQueue.pop();
        }
        
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
    Combo comboManager;
    PlayerRecord record;

public:
    void start() {
        std::cout << "=== Starting Game ===" << std::endl;
        std::cout << "Game started. Enjoy!" << std::endl;

        time.setTimeLimit(60);
        time.startTimer();
        std::cout << "Timer started: 1 minute from now. GO!" << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(62));
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

    void exit() {
        std::cout << "Exiting the game menu." << std::endl;
        // aqui se deberia de volver al menu?, idk
        std::exit(0);
    }

    void showGameMenu() {
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

    void showMenu() {
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
    }
};
int main() {
    GameMenu gameMenu;
    gameMenu.showGameMenu();
    return 0;
}
