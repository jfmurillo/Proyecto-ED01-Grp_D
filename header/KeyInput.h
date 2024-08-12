#ifndef KEYINPUT_H
#define KEYINPUT_H

#include <queue>
#include <string>
#include "Combo.h"

class KeyInput {
private:
    std::queue<char> keyQueue;
    Combo& comboManager;

public:
    KeyInput(Combo& comboMgr);

    void addKey(char key);
    std::string getCurrentSequence() const;
    void processInput();
    void clearKeys();
};

#endif
