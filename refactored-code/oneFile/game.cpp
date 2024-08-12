#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <unordered_map>
#include "windows.h"

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

template <typename T>
class Queue {
private:
    list<T> elements;

public:
    void enqueue(T value) {
        elements.push_back(value);
    }

    T dequeue() {
        if (!elements.empty()) {
            T frontElement = elements.front();
            elements.pop_front();
            return frontElement;
        } else {
            throw std::out_of_range("Queue is empty");
        }
    }

    T peek() {
        if (!elements.empty()) {
            return elements.front();
        } else {
            throw std::out_of_range("Queue is empty");
        }
    }

    bool isEmpty() {
        return elements.empty();
    }

    int size() {
        return elements.size();
    }
    void printQueue() const {
        if (elements.empty()) {
            std::cout << "Queue is empty" << std::endl;
        } else {
            for (const auto& element : elements) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
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

struct Node {
    string name;
    string sequence;
    Node* next;

    Node(const string& name, const string& sequence) : name(name), sequence(sequence), next(nullptr) {}
};

class Combo {
private:
    Node* head;

public:
    Combo() : head(nullptr) {}

    void createCombo(const string name, const string sequence) {
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

    bool checkAndExecuteCombo(const std::string& inputSequence) {
    Node* current = head;

    std::cout << "Input Sequence: " << inputSequence << std::endl;

    // Primero, encuentra el combo más largo que coincida con la secuencia
    std::string longestMatch = "";
    Node* bestMatch = nullptr;

    while (current) {
        std::cout << "Checking against combo sequence: " << current->sequence << std::endl;
        if (inputSequence.find(current->sequence) != std::string::npos) {
            if (current->sequence.length() > longestMatch.length()) {
                longestMatch = current->sequence;
                bestMatch = current;
            }
        }
        current = current->next;
    }

    if (bestMatch) {
        std::cout << "Combo '" << bestMatch->name << "' with sequence: " << bestMatch->sequence << std::endl;
        return true;
    } else {
        std::cout << "Secuencia no encontrada en la lista de combos." << std::endl;
        return false;
    }
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
};
class KeyInput {
private:
    Queue<string> keyQueue;

public:
    void addKeyPress(const string& key) {
        keyQueue.enqueue(key);
    }

    string getFirstKeyPressed() {
        if (keyQueue.isEmpty()) {
            return "";
        }
        return keyQueue.dequeue();
    }

    string getKeySequence() {
        string keySequence;
        while (!keyQueue.isEmpty()) {
            keySequence += keyQueue.dequeue();
        }
        return keySequence;
    }
};


class GameMenu {
private:
    PlayerRecord playerRecord;
    Combo comboManager;
    KeyInput keyInput;
    Timer timer;

    bool isTrainingModeActive;
    bool trainingMode;
    bool exitRequested;
    bool runTimer;

    void executeCombo() {
        string sequence = keyInput.getKeySequence();
        if (!sequence.empty()) {
            comboManager.checkAndExecuteCombo(sequence);
        }
    }

    void processTraining() {
        std::cout << "Training mode activated.\n";
        std::cout << "Press 'E' to end the game.\n";

        char key;
        while (trainingMode) {
            std::cin >> key;
            if (key == 'E' || key == 'e') {
                std::cout << "Exiting game...\n";
                trainingMode = false;
                break;
            }
            keyInput.addKeyPress(string(1, key));
            executeCombo();
        }
    }

    void createPredefinedCombos() {
        comboManager.createCombo("Combo1", "A");
        comboManager.createCombo("Combo2", "AB");
        comboManager.createCombo("Combo3", "ABC");
        comboManager.createCombo("Combo4", "ABCD");
        comboManager.createCombo("Combo5", "ABCDE");
        comboManager.createCombo("Combo6", "ABCDEF");
        comboManager.createCombo("Combo7", "ABCDEFG");
        comboManager.createCombo("Combo8", "ABCDEFGH");
    }

public:
    GameMenu() : isTrainingModeActive(false), trainingMode(false), exitRequested(false), runTimer(false) {}

    void showGameMenu() {
        createPredefinedCombos(); 

        int choice;
        do {
            std::cout << "1. Player settings\n";
            std::cout << "2. Combo settings\n";
            std::cout << "3. Enter training mode\n";
            std::cout << "4. Start game\n";
            std::cout << "5. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore(); 

            switch (choice) {
                case 1:
                    playerSettings();
                    break;
                case 2:
                    comboSettings();
                    break;
                case 3:
                    trainingMode = true;
                    processTraining();
                    break;
                case 4:
                    start();
                    break;
                case 5:
                    exitRequested = true;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } while (!exitRequested);
    }

    void playerSettings() {
        int choice;
        do {
            std::cout << "Player Settings:\n";
            std::cout << "1. Register new player\n";
            std::cout << "2. Delete player\n";
            std::cout << "3. Show player records\n";
            std::cout << "4. Back to main menu\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore();  

            switch (choice) {
                case 1: {
                    std::string nickname, name, lastName, email;
                    int age;
                    std::cout << "Enter nickname: ";
                    std::getline(std::cin, nickname);
                    std::cout << "Enter name: ";
                    std::getline(std::cin, name);
                    std::cout << "Enter last name: ";
                    std::getline(std::cin, lastName);
                    std::cout << "Enter email: ";
                    std::getline(std::cin, email);
                    std::cout << "Enter age: ";
                    std::cin >> age;
                    std::cin.ignore();  

                    Player player(nickname, name, lastName, email, age);
                    playerRecord.registerPlayer(player);
                    break;
                }
                case 2: {
                    std::string nickname;
                    std::cout << "Enter player nickname to delete: ";
                    std::getline(std::cin, nickname);
                    playerRecord.deletePlayer(nickname);
                    break;
                }
                case 3:
                    playerRecord.showPlayerRecord();
                    break;
                case 4:
                    return;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } while (true);
    }

    void comboSettings() {
        int choice;
        do {
            std::cout << "Combo Settings:\n";
            std::cout << "1. Create new combo\n";
            std::cout << "2. List combos\n";
            std::cout << "3. Remove combo\n";
            std::cout << "4. Back to main menu\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore();  

            switch (choice) {
                case 1: {
                    std::string name, sequence;
                    std::cout << "Enter combo name: ";
                    std::getline(std::cin, name);
                    std::cout << "Enter combo sequence: ";
                    std::getline(std::cin, sequence);

                    comboManager.createCombo(name, sequence);
                    break;
                }
                case 2:
                    comboManager.listCombos();
                    break;
                case 3: {
                    std::string name;
                    std::cout << "Enter combo name to delete: ";
                    std::getline(std::cin, name);
                    comboManager.removeCombo(name);
                    break;
                }
                case 4:
                    return;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } while (true);
    }

    void start() {
        std::cout << "=== Starting Game ===" << std::endl;
        std::cout << "Game started. Enjoy!" << std::endl;

        timer.setTimeLimit(60);  
        timer.startTimer();
        std::cout << "Timer started: 1 minute from now. GO!" << std::endl;


        std::string inputSequence;
        char key;

        //KeyInput keyInput;
        //char key = '\0';

        while (!timer.isTimeExceeded()) {
            std::cout << "Press a key: ";
            std::cin >> key;
            inputSequence += key;

            if (comboManager.checkAndExecuteCombo(inputSequence)) {
            inputSequence.clear();  // Limpiar la secuencia si se ejecutó un combo

            //keyInput.addKeyPress(string(1, key));  
            //executeCombo();
        }

        timer.stopTimer();
        std::cout << "Time limit exceeded!" << std::endl;
        std::cout << "Elapsed time: " << timer.getElapsedTime() << " seconds" << std::endl;
    }
  }
};

int main() {
    GameMenu gameMenu;
    gameMenu.showGameMenu();
    return 0;
}