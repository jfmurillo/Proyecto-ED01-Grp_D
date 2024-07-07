#include "../header/GameMenu.h"
#include "../header/Menu.h"
#include "../header/PlayerRecord.h"
#include <iostream>

int main() {
    PlayerRecord playerRecord; 
    GameMenu gameMenu;
    Menu menu(playerRecord,gameMenu);


    gameMenu.showGameMenu();

    std::cout << "=== Exiting Program ===" << std::endl;
    return 0;
}
