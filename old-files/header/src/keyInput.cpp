// #include "KeyInput.h"
// #include <iostream>

// // Constructor que inicializa la cola de teclas
// KeyInput::KeyInput() {}

// // Método para agregar una tecla validada
// void KeyInput::addKey(char key) {
//     if (isalnum(key)) { // Verificar si el carácter es letra o dígito
//         keys.push(key);
//     } else {
//         std::cout << "Tecla no válida ingresada: " << key << ". Se ignora." << std::endl;
//     }
// }

// // Método para eliminar y devolver la primera tecla en la cola
// char KeyInput::dequeueKey() {
//     if (keys.empty()) {
//         return '\0'; // Si la cola está vacía, retornar carácter nulo
//     }
//     char frontKey = keys.front();
//     keys.pop();
//     return frontKey;
// }

// // Método para obtener las teclas en la cola
// std::queue<char> KeyInput::getKeys() const {
//     return keys;
// }

// // Método para limpiar la cola de teclas
// void KeyInput::clearKeys() {
//     std::queue<char> empty;
//     std::swap(keys, empty); // Vaciar la cola actual intercambiándola con una cola vacía
// }

// // Método para mostrar las teclas en la cola como una cadena
// std::string KeyInput::showKeys() const {
//     std::stringstream ss;
//     std::queue<char> temp = keys; // Crear una copia de la cola
//     while (!temp.empty()) {
//         ss << temp.front() << " -> ";
//         temp.pop();
//     }
//     std::string result = ss.str();
//     if (!result.empty()) {
//         result = result.substr(0, result.size() - 4); // Eliminar la última flecha
//     }
//     result += " registradas en la cola";
//     return result;
// }

// // Método para obtener la siguiente tecla en la cola
// char KeyInput::nextKey() const {
//     return keys.empty() ? '\0' : keys.front();
// }

// // Método para verificar si se ha alcanzado el mínimo de teclas
// bool KeyInput::isMinKeysReached() const {
//     return keys.size() >= 8;
// }
