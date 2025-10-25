#pragma once
#include <string>
#include <locale>

class RouteCipher {
private:
    int columns;
    
public:
    RouteCipher(int key);
    void setKey(int key);
    int getKey() const;
    std::wstring encrypt(const std::wstring& text);
    std::wstring decrypt(const std::wstring& text);
};

