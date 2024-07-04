#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>
using std::list;
using std::string;
using std::vector;

class Player{
private:
  string nickname;
  string name;
  string lastName;
  string email;
  int age;

public:
  Player(string nickname, string name, string lastName, string email, int age)
      : nickname(nickname), name(name), lastName(lastName), email(email), age(age) {}

  // getter
  string getNickName() const { return nickname; }
  string getName() const { return name; }
  string getLastName() const { return lastName; }
  string getEmail() const { return email; }
  int getAge() const { return age; }

  // setter
  void setName(const string &name) { this->name = name; }
  void setLastName(const string &lastName) { this->lastName = lastName; }
  void setEmail(const string &email) { this->email = email; }
  void setAge(int age) { this->age = age; }

  // methods
  void displayPlayer() const{
    std::cout << "ID: " << nickname << ", Name: " << name << ", Last Name: " << lastName
              << ", Email: " << email << ", Age: " << age << std::endl;
  }

  Player getPlayerbyID(string nickname){
    std::cout << "Please enter player nickname: ";
    return *this;
  }

  Player modifyPlayer(string nickname){

    return *this;
  };
};

class PlayerRecord{
private:
  list<Player> players;

public:
  void registerPlayer(const Player player){
    players.push_back(player);
  }

  bool deletePlayer(string nickname){
    for (auto i = players.begin(); i != players.end(); ++i){
      if (i->getNickName() == nickname){
        players.erase(i);
        return true;
      }
    }
    std::cout << "Player not found" << std::endl;
    return false;
  }

  void showPlayerRecord() const{
    if (players.empty()){
      std::cout << "No players registered." << std::endl;
      return;
    }
    for (const auto &player : players){
      player.displayPlayer();
    }
  }

  int findPlayerById(string nickname) const{
    auto i = find_if(players.begin(), players.end(), [nickname](const Player &player)
                     { return player.getNickName() == nickname; });

    if (i != players.end()){
      return distance(players.begin(), i);
    }
    std::cout << "Not found" << std::endl;
    return -1;
  }
};

int main() {

};