#include "Combo.h"
#include <iostream>

Node::Node(const std::string& name, const std::string& sequence)
    : name(name), sequence(sequence), next(nullptr) {}

Combo::Combo() : head(nullptr) {}

Combo::~Combo() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

void Combo::createCombo(const std::string name, const std::string sequence) {
    Node* newNode = new Node(name, sequence);
    if (!head) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    std::cout << "Combo '" << name << "' created using: " << sequence << std::endl;
}

std::string Combo::obtainSequence(const std::string& name) const {
    Node* current = head;
    while (current) {
        if (current->name == name) {
            return current->sequence;
        }
        current = current->next;
    }
    return "Combo not found.";
}

void Combo::executeCombo(const std::string& name) {
    Node* current = head;
    while (current) {
        if (current->name == name) {
            std::cout << "Combo '" << name << "' with sequence: " << current->sequence << std::endl;
            return;
        }
        current = current->next;
    }
    std::cout << "Combo '" << name << "' not found." << std::endl;
}

void Combo::removeCombo(const std::string& name) {
    if (!head) {
        std::cout << "Combo list is empty." << std::endl;
        return;
    }
    Node* current = head;
    Node* prev = nullptr;
    while (current) {
        if (current->name == name) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            std::cout << "Combo '" << name << "' deleted." << std::endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    std::cout << "Combo '" << name << "' not found." << std::endl;
}

void Combo::listCombos() const {
    if (!head) {
        std::cout << "No combos on combo list." << std::endl;
        return;
    }
    std::cout << "=== Combo List ===" << std::endl;
    Node* current = head;
    while (current) {
        std::cout << "Combo: " << current->name << ", Sequence: " << current->sequence << std::endl;
        current = current->next;
    }
}

std::string Combo::findCombo(const std::string& sequence) const {
    Node* current = head;
    while (current) {
        if (current->sequence == sequence) {
            return current->name;
        }
        current = current->next;
    }
    return "Combo with sequence '" + sequence + "' not found.";
}

void Combo::checkAndExecuteCombo(const std::string& inputSequence) {
    Node* current = head;
    while (current) {
        if (current->sequence == inputSequence) {
            std::cout << "Combo: " << current->name << ". executing..." << std::endl;
            executeCombo(current->name);
            return;
        }
        current = current->next;
    }
    std::cout << "Combo not found using sequence: " << inputSequence << std::endl;
}
