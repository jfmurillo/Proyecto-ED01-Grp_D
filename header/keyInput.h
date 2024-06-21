#ifndef KEYINPUT_H
#define KEYINPUT_H

#include <queue>
#include <string>
#include <sstream>
#include <cctype> 

class KeyInput {
private:
    std::queue<char> keys; 

public:
    KeyInput();

    void addKey(char key); // Agregar tecla validada
    char dequeueKey(); // Eliminar la primera tecla en la cola
    std::queue<char> getKeys() const; // Obtener las teclas en la cola
    void clearKeys(); // Limpiar la cola de teclas
    std::string showKeys() const; // Mostrar las teclas en la cola
    char nextKey() const; // Obtener la siguiente tecla en la cola
    bool isMinKeysReached() const; // Verificar si se ha alcanzado el mínimo de teclas
};

#endif
