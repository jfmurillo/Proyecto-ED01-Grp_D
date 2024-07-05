#ifndef MENU_H
#define MENU_H

#include "PlayerRecord.h"
#include "GameMenu.h"

class Menu {
private:
    GameMenu gameMenu;
    PlayerRecord record;

    void newPlayerMenu();
    void existingPlayerMenu();

public:
    void showMenu();
};

#endif 