#pragma once
#include <string>
#include <vector>

class routeCipher
{
private:
    int key; // количество столбцов
    
    // Вспомогательные методы
    std::string getValidText(const std::string& text);
    std::vector<std::vector<char>> createTable(const std::string& text, bool encrypt);
    std::string readTableEncrypt(const std::vector<std::vector<char>>& table);
    std::string readTableDecrypt(const std::vector<std::vector<char>>& table);

public:
    routeCipher() = delete;
    routeCipher(int k);
    
    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& text);
};
