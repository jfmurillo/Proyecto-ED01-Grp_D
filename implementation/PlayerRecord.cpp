#include "PlayerRecord.h"
#include <iostream>
#include <algorithm>

void PlayerRecord::registerPlayer(const Player player) {
    players.push_back(player);
}

bool PlayerRecord::deletePlayer(std::string nickname) {
    for (auto i = players.begin(); i != players.end(); ++i) {
        if (i->getNickName() == nickname) {
            players.erase(i);
            return true;
        }
    }
    std::cout << "Player not found" << std::endl;
    return false;
}

void PlayerRecord::showPlayerRecord() const {
    if (players.empty()) {
        std::cout << "No players registered." << std::endl;
        return;
    }
    for (const auto &player : players) {
        player.displayPlayer();
    }
}

int PlayerRecord::findPlayerById(std::string nickname) const {
    auto i = std::find_if(players.begin(), players.end(), [nickname](const Player &player) {
        return player.getNickName() == nickname;
    });

    if (i != players.end()) {
        return std::distance(players.begin(), i);
    }
    std::cout << "Not found" << std::endl;
    return -1;
}

bool PlayerRecord::hasPlayers() const {
    return !players.empty();
}
