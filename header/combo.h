#ifndef COMBO_H
#define COMBO_H

#include <string>

class Combo {
private:
    int comboID;
    std::string sequence;

public:
    Combo(int comboID, const std::string& sequence);

    int getComboID() const;
    const std::string& getSequence() const;
};

#endif
