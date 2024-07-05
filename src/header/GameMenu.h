#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "Timer.h"
#include "Combo.h"
#include "PlayerRecord.h"
#include "Menu.h"
#include "GameMenu.h"

class GameMenu {
private:
    Timer time;
    Combo comboManager;
    PlayerRecord record;
    Menu mainMenu;

public:
    void start();
    void trainingMode();
    void exit();
    void showGameMenu();
};

#endif
