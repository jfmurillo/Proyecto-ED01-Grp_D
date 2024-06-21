#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    int playerID;
    std::string name;
    std::string lastName;
    std::string email;
    int age;

    Player(int pID, std::string name, std::string lastName, std::string email, int age);
};

#endif 
