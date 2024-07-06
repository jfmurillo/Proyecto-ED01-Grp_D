#ifndef PLAYER_RECORD_H
#define PLAYER_RECORD_H

#include <list>
#include "Player.h"

class PlayerRecord {
private:
    std::list<Player> players;

public:
    void registerPlayer(const Player player);
    bool deletePlayer(std::string nickname);
    void showPlayerRecord() const;
    int findPlayerById(std::string nickname) const;
    bool hasPlayers() const;
};

#endif 
