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

class CustomQueue {
private:
    queue<string> internalQueue;

public:
    // Constructor por defecto
    CustomQueue() {}

    // Añadir un elemento a la cola
    void enqueue(const string& element) {
        internalQueue.push(element);
        std::cout << "Element " << element << " added to the queue.\n";
    }

    // Eliminar el primer elemento de la cola
    string dequeue() {
        if (internalQueue.empty()) {
            std::cout << "Queue is empty. Cannot dequeue.\n";
            return "";
        } else {
            string frontElement = internalQueue.front();
            internalQueue.pop();
            std::cout << "Element " << frontElement << " removed from the queue.\n";
            return frontElement;
        }
    }

    // Verificar si la cola está vacía
    bool isEmpty() const {
        return internalQueue.empty();
    }

    // Obtener el primer elemento de la cola sin eliminarlo
    string front() const {
        if (internalQueue.empty()) {
            std::cout << "Queue is empty.\n";
            return "";
        } else {
            return internalQueue.front();
        }
    }

    // Obtener el tamaño de la cola
    size_t size() const {
        return internalQueue.size();
    }

    // Mostrar los elementos de la cola
    void displayQueue() const {
        if (internalQueue.empty()) {
            std::cout << "Queue is empty.\n";
        } else {
            std::queue<string> tempQueue = internalQueue;
            std::cout << "Queue elements: ";
            while (!tempQueue.empty()) {
                std::cout << tempQueue.front() << " ";
                tempQueue.pop();
            }
            std::cout << std::endl;
        }
    }
};

// Código de prueba para la clase CustomQueue
int main() {
    CustomQueue myQueue;

    myQueue.enqueue("A");
    myQueue.enqueue("B");
    myQueue.enqueue("C");

    myQueue.displayQueue();

    myQueue.dequeue();
    myQueue.displayQueue();

    std::cout << "Front element: " << myQueue.front() << std::endl;
    std::cout << "Queue size: " << myQueue.size() << std::endl;
    std::cout << "Is queue empty? " << (myQueue.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}






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

    void executeCombo(const string& inputSequence) {
        Node* current = head;
        while (current) {
            if (inputSequence.find(current->sequence) != string::npos) {
                std::cout << "Combo '" << current->name << "' with sequence: " << current->sequence << std::endl;
                return;
            }
            current = current->next;
        }
        std::cout << "Combo not found using sequence: " << inputSequence << std::endl;
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
                return;
            }
            current = current->next;
        }
        std::cout << "Sequence not found in combo list." << std::endl;
    }
};

class CustomQueue {
private:
    queue<string> internalQueue;

public:
    CustomQueue() {}

    void enqueue(const string& element) {
        internalQueue.push(element);
        std::cout << "Element " << element << " added to the queue.\n";
    }

    string dequeue() {
        if (internalQueue.empty()) {
            std::cout << "Queue is empty. Cannot dequeue.\n";
            return "";
        } else {
            string frontElement = internalQueue.front();
            internalQueue.pop();
            std::cout << "Element " << frontElement << " removed from the queue.\n";
            return frontElement;
        }
    }

    bool isEmpty() const {
        return internalQueue.empty();
    }

    string front() const {
        if (internalQueue.empty()) {
            std::cout << "Queue is empty.\n";
            return "";
        } else {
            return internalQueue.front();
        }
    }

    size_t size() const {
        return internalQueue.size();
    }

    void displayQueue() const {
        if (internalQueue.empty()) {
            std::cout << "Queue is empty.\n";
        } else {
            std::queue<string> tempQueue = internalQueue;
            std::cout << "Queue elements: ";
            while (!tempQueue.empty()) {
                std::cout << tempQueue.front() << " ";
                tempQueue.pop();
            }
            std::cout << std::endl;
        }
    }
};

class KeyInput {
private:
    CustomQueue keyQueue;

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
public:
    void showGameMenu() {
        // Menu principal
        std::cout << "==== Game Menu ====" << std::endl;
        std::cout << "1. Player Registration" << std::endl;
        std::cout << "2. Create Combos" << std::endl;
        std::cout << "3. Set Timer" << std::endl;
        std::cout << "4. Key Input" << std::endl;
        std::cout << "5. Exit" << std::endl;

        int choice;
        std::cin >> choice;

        PlayerRecord playerRecord;
        Combo comboList;
        Timer timer;
        KeyInput keyInput;

        while (choice != 5) {
            switch (choice) {
            case 1: {
                std::cout << "Player Registration Menu" << std::endl;
                std::cout << "1. Register Player" << std::endl;
                std::cout << "2. Delete Player" << std::endl;
                std::cout << "3. Show Player Record" << std::endl;
                std::cout << "4. Return to Main Menu" << std::endl;

                int playerChoice;
                std::cin >> playerChoice;

                while (playerChoice != 4) {
                    if (playerChoice == 1) {
                        string nickname, name, lastName, email;
                        int age;
                        std::cout << "Enter Nickname: ";
                        std::cin >> nickname;
                        std::cout << "Enter Name: ";
                        std::cin >> name;
                        std::cout << "Enter Last Name: ";
                        std::cin >> lastName;
                        std::cout << "Enter Email: ";
                        std::cin >> email;
                        std::cout << "Enter Age: ";
                        std::cin >> age;

                        Player player(nickname, name, lastName, email, age);
                        playerRecord.registerPlayer(player);

                        std::cout << "Player registered successfully." << std::endl;
                    } else if (playerChoice == 2) {
                        string nickname;
                        std::cout << "Enter Nickname to Delete: ";
                        std::cin >> nickname;

                        if (playerRecord.deletePlayer(nickname)) {
                            std::cout << "Player deleted successfully." << std::endl;
                        }
                    } else if (playerChoice == 3) {
                        playerRecord.showPlayerRecord();
                    }

                    std::cout << "Player Registration Menu" << std::endl;
                    std::cout << "1. Register Player" << std::endl;
                    std::cout << "2. Delete Player" << std::endl;
                    std::cout << "3. Show Player Record" << std::endl;
                    std::cout << "4. Return to Main Menu" << std::endl;
                    std::cin >> playerChoice;
                }
                break;
            }
            case 2: {
                std::cout << "Combo Menu" << std::endl;
                std::cout << "1. Create Combo" << std::endl;
                std::cout << "2. Execute Combo" << std::endl;
                std::cout << "3. Remove Combo" << std::endl;
                std::cout << "4. List Combos" << std::endl;
                std::cout << "5. Return to Main Menu" << std::endl;

                int comboChoice;
                std::cin >> comboChoice;

                while (comboChoice != 5) {
                    if (comboChoice == 1) {
                        string name, sequence;
                        std::cout << "Enter Combo Name: ";
                        std::cin >> name;
                        std::cout << "Enter Combo Sequence: ";
                        std::cin >> sequence;

                        comboList.createCombo(name, sequence);
                    } else if (comboChoice == 2) {
                        string inputSequence;
                        std::cout << "Enter Input Sequence to Execute: ";
                        std::cin >> inputSequence;

                        comboList.executeCombo(inputSequence);
                    } else if (comboChoice == 3) {
                        string name;
                        std::cout << "Enter Combo Name to Remove: ";
                        std::cin >> name;

                        comboList.removeCombo(name);
                    } else if (comboChoice == 4) {
                        comboList.listCombos();
                    }

                    std::cout << "Combo Menu" << std::endl;
                    std::cout << "1. Create Combo" << std::endl;
                    std::cout << "2. Execute Combo" << std::endl;
                    std::cout << "3. Remove Combo" << std::endl;
                    std::cout << "4. List Combos" << std::endl;
                    std::cout << "5. Return to Main Menu" << std::endl;
                    std::cin >> comboChoice;
                }
                break;
            }
            case 3: {
                std::cout << "Timer Menu" << std::endl;
                std::cout << "1. Set Timer" << std::endl;
                std::cout << "2. Start Timer" << std::endl;
                std::cout << "3. Stop Timer" << std::endl;
                std::cout << "4. Check Time Exceeded" << std::endl;
                std::cout << "5. Get Elapsed Time" << std::endl;
                std::cout << "6. Return to Main Menu" << std::endl;

                int timerChoice;
                std::cin >> timerChoice;

                while (timerChoice != 6) {
                    if (timerChoice == 1) {
                        int timeLimit;
                        std::cout << "Enter Time Limit in Seconds: ";
                        std::cin >> timeLimit;

                        timer.setTimeLimit(timeLimit);
                        std::cout << "Time limit set to " << timeLimit << " seconds." << std::endl;
                    } else if (timerChoice == 2) {
                        timer.startTimer();
                        std::cout << "Timer started." << std::endl;
                    } else if (timerChoice == 3) {
                        timer.stopTimer();
                        std::cout << "Timer stopped." << std::endl;
                    } else if (timerChoice == 4) {
                        if (timer.isTimeExceeded()) {
                            std::cout << "Time limit exceeded." << std::endl;
                        } else {
                            std::cout << "Time limit not exceeded." << std::endl;
                        }
                    } else if (timerChoice == 5) {
                        std::cout << "Elapsed Time: " << timer.getElapsedTime() << " seconds." << std::endl;
                    }

                    std::cout << "Timer Menu" << std::endl;
                    std::cout << "1. Set Timer" << std::endl;
                    std::cout << "2. Start Timer" << std::endl;
                    std::cout << "3. Stop Timer" << std::endl;
                    std::cout << "4. Check Time Exceeded" << std::endl;
                    std::cout << "5. Get Elapsed Time" << std::endl;
                    std::cout << "6. Return to Main Menu" << std::endl;
                    std::cin >> timerChoice;
                }
                break;
            }
            case 4: {
                std::cout << "Key Input Menu" << std::endl;
                std::cout << "1. Add Key Press" << std::endl;
                std::cout << "2. Get First Key Pressed" << std::endl;
                std::cout << "3. Get Key Sequence" << std::endl;
                std::cout << "4. Return to Main Menu" << std::endl;

                int keyInputChoice;
                std::cin >> keyInputChoice;

                while (keyInputChoice != 4) {
                    if (keyInputChoice == 1) {
                        string key;
                        std::cout << "Enter Key Press: ";
                        std::cin >> key;

                        keyInput.addKeyPress(key);
                    } else if (keyInputChoice == 2) {
                        std::cout << "First Key Pressed: " << keyInput.getFirstKeyPressed() << std::endl;
                    } else if (keyInputChoice == 3) {
                        std::cout << "Key Sequence: " << keyInput.getKeySequence() << std::endl;
                    }

                    std::cout << "Key Input Menu" << std::endl;
                    std::cout << "1. Add Key Press" << std::endl;
                    std::cout << "2. Get First Key Pressed" << std::endl;
                    std::cout << "3. Get Key Sequence" << std::endl;
                    std::cout << "4. Return to Main Menu" << std::endl;
                    std::cin >> keyInputChoice;
                }
                break;
            }
            }

            std::cout << "==== Game Menu ====" << std::endl;
            std::cout << "1. Player Registration" << std::endl;
            std::cout << "2. Create Combos" << std::endl;
            std::cout << "3. Set Timer" << std::endl;
            std::cout << "4. Key Input" << std::endl;
            std::cout << "5. Exit" << std::endl;
            std::cin >> choice;
        }
    }
};

int main() {
    GameMenu gameMenu;
    gameMenu.showGameMenu();
    return 0;
}
