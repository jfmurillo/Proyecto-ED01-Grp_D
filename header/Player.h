#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string nickname;
    std::string name;
    std::string lastName;
    std::string email;
    int age;

public:
    Player(std::string nickname, std::string name, std::string lastName, std::string email, int age);

    std::string getNickName() const;
    std::string getName() const;
    std::string getLastName() const;
    std::string getEmail() const;
    int getAge() const;

    void setName(const std::string &name);
    void setLastName(const std::string &lastName);
    void setEmail(const std::string &email);
    void setAge(int age);

    void displayPlayer() const;
    Player getPlayerbyID(std::string nickname);
    Player modifyPlayer(std::string nickname);
};

#endif
