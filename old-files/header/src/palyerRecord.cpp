// #include "PlayerRecord.h"
// #include <iostream>
// #include <algorithm>
// #include <vector>

// PlayerRecord::PlayerRecord() {
//     createPlayerRecord();
// }

// void PlayerRecord::createPlayerRecord() {
//     players.clear(); 
// }

// void PlayerRecord::registerPlayer(const Player& player) {
//     bool exists = false;
//     for (const auto& p : players) {
//         if (p.playerID == player.playerID) {
//             exists = true;
//             break;
//         }
//     }
//     if (!exists) {
//         players.push_back(player);
//     }
// }

// void PlayerRecord::deletePlayer(int playerID) {
//     players.erase(std::remove_if(players.begin(), players.end(),
//                                  [playerID](const Player& player) { return player.playerID == playerID; }),
//                   players.end());
// }

// void PlayerRecord::showPlayerRecord() const {
//     for (const auto& player : players) {
//         std::cout << "ID: " << player.playerID
//                   << ", Name: " << player.name
//                   << ", Last name: " << player.last_name
//                   << ", Email: " << player.email
//                   << ", Age: " << player.age
//                   << std::endl;
//     }
// }
