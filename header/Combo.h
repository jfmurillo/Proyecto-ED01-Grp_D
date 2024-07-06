#ifndef COMBO_H
#define COMBO_H

#include <string>

struct Node {
    std::string name;
    std::string sequence;
    Node* next;

    Node(const std::string& name, const std::string& sequence);
};

class Combo {
private:
    Node* head;

public:
    Combo();
    ~Combo();

    void createCombo(const std::string name, const std::string sequence);
    std::string obtainSequence(const std::string& name) const;
    void executeCombo(const std::string& name);
    void removeCombo(const std::string& name);
    void listCombos() const;
    std::string findCombo(const std::string& sequence) const;
    void checkAndExecuteCombo(const std::string& inputSequence);
};

#endif