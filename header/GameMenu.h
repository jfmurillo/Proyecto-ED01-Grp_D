#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "../header/Timer.h"
#include "../header/Combo.h"
#include "../header/PlayerRecord.h"

class Menu;

class GameMenu {
private:
    Timer time;
    Combo comboManager;
    PlayerRecord record;
    Menu* mainMenu;

public:
    GameMenu();
    ~GameMenu();
    void start();
    void trainingMode();
    void exit();
    void showGameMenu();
};

#endif
