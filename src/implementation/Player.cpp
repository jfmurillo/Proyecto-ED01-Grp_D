#include "Player.h"
#include <iostream>

Player::Player(std::string nickname, std::string name, std::string lastName, std::string email, int age)
    : nickname(nickname), name(name), lastName(lastName), email(email), age(age) {}

std::string Player::getNickName() const { return nickname; }
std::string Player::getName() const { return name; }
std::string Player::getLastName() const { return lastName; }
std::string Player::getEmail() const { return email; }
int Player::getAge() const { return age; }

void Player::setName(const std::string &name) { this->name = name; }
void Player::setLastName(const std::string &lastName) { this->lastName = lastName; }
void Player::setEmail(const std::string &email) { this->email = email; }
void Player::setAge(int age) { this->age = age; }

void Player::displayPlayer() const {
    std::cout << "ID: " << nickname << ", Name: " << name << ", Last Name: " << lastName
              << ", Email: " << email << ", Age: " << age << std::endl;
}

Player Player::getPlayerbyID(std::string nickname) {
    std::cout << "Please enter player nickname: ";
    return *this;
}

Player Player::modifyPlayer(std::string nickname) {
    return *this;
}
