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

public:
    void start();
    void trainingMode();
    void exit();
    void showGameMenu();

    //metodos del menu anterior(main)
    void showMenu();
    void newPlayerMenu();
    void existingPlayerMenu();

};

#endif
