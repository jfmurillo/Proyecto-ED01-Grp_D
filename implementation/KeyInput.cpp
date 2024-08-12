// KeyInput.cpp

#include "KeyInput.h"
#include <iostream>

KeyInput::KeyInput(Combo& comboMgr) : comboManager(comboMgr) {}

void KeyInput::addKey(char key) {
    keyQueue.push(key);
    std::cout << "Key entered: " << key << std::endl;
}

std::string KeyInput::getCurrentSequence() const {
    std::string sequence;
    std::queue<char> tempQueue = keyQueue;
    while (!tempQueue.empty()) {
        sequence += tempQueue.front();
        tempQueue.pop();
    }
    return sequence;
}

void KeyInput::processInput() {
    std::string currentSequence = getCurrentSequence();
    std::cout << "Actual sequence: " << currentSequence << std::endl;
    comboManager.checkAndExecuteCombo(currentSequence);
    while (!keyQueue.empty()) {
        keyQueue.pop();
    }
}

void KeyInput::clearKeys() {
    while (!keyQueue.empty()) {
        keyQueue.pop();
    }
}
