#ifndef MENU_H
#define MENU_H

#include "../header/PlayerRecord.h"

class GameMenu;

class Menu {
private:
    GameMenu& gameMenu;
    PlayerRecord& record;

    void newPlayerMenu();
    void existingPlayerMenu();

public:

    Menu(PlayerRecord& record, GameMenu& gameMenu);
    void showMenu();
};

#endif 