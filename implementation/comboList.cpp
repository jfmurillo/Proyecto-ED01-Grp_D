#include "comboList.h"

ComboList::ComboList() {}

void ComboList::createCombo(int comboID, const std::string& sequence) {
    Combo nuevoCombo(comboID, sequence);
    comboList.push_back(nuevoCombo);
}

const std::string* ComboList::getSequence(int comboID) const {
    for (const Combo& combo : comboList) {
        if (combo.getComboID() == comboID) {
            return &combo.getSequence();
        }
    }
    return nullptr;
}

bool ComboList::executeCombo(const std::string& sequence) const {
    for (const Combo& combo : comboList) {
        if (combo.getSequence() == sequence) {
            return true;
        }
    }
    return false;
}
