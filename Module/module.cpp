#include "routeCipher.h"
#include <algorithm>
#include <stdexcept>

routeCipher::routeCipher(int k)
{
    if (k <= 0) {
        throw std::invalid_argument("Ключ должен быть положительным числом");
    }
    key = k;
}

std::string routeCipher::encrypt(const std::string& text)
{
    std::string valid_text = getValidText(text);
    std::vector<std::vector<char>> table = createTable(valid_text, true);
    return readTableEncrypt(table);
}

std::string routeCipher::decrypt(const std::string& text)
{
    std::string valid_text = getValidText(text);
    std::vector<std::vector<char>> table = createTable(valid_text, false);
    return readTableDecrypt(table);
}

std::string routeCipher::getValidText(const std::string& text)
{
    if (text.empty()) {
        throw std::invalid_argument("Текст не может быть пустым");
    }
    
    std::string result;
    for (char c : text) {
        if (isalpha(c)) {
            result.push_back(toupper(c));
        }
    }
    
    if (result.empty()) {
        throw std::invalid_argument("Текст не содержит букв");
    }
    
    return result;
}

std::vector<std::vector<char>> routeCipher::createTable(const std::string& text, bool encrypt)
{
    int text_length = text.length();
    int rows = (text_length + key - 1) / key; // Округление вверх
    
    std::vector<std::vector<char>> table(rows, std::vector<char>(key, ' '));
    
    if (encrypt) {
        // Запись по горизонтали слева направо, сверху вниз
        for (int i = 0; i < text_length; i++) {
            int row = i / key;
            int col = i % key;
            table[row][col] = text[i];
        }
    } else {
        // Запись сверху вниз, справа налево (для дешифрования)
        int index = 0;
        for (int col = key - 1; col >= 0; col--) {
            for (int row = 0; row < rows; row++) {
                if (index < text_length) {
                    table[row][col] = text[index++];
                }
            }
        }
    }
    
    return table;
}

std::string routeCipher::readTableEncrypt(const std::vector<std::vector<char>>& table)
{
    std::string result;
    int rows = table.size();
    int cols = table[0].size();
    
    // Чтение сверху вниз, справа налево
    for (int col = cols - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            if (table[row][col] != ' ') {
                result.push_back(table[row][col]);
            }
        }
    }
    
    return result;
}

std::string routeCipher::readTableDecrypt(const std::vector<std::vector<char>>& table)
{
    std::string result;
    int rows = table.size();
    int cols = table[0].size();
    
    // Чтение по горизонтали слева направо, сверху вниз
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (table[row][col] != ' ') {
                result.push_back(table[row][col]);
            }
        }
    }
    
    return result;
}
