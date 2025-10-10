#pragma once
#include <vector>
#include <string>
#include <map>
using namespace std;
class modAlphaCipher
{
private:
wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //алфавит по порядку
    map<wchar_t, int> alphaNum; //ассоциативный массив "номер по символу"
    vector<int> key; //ключ
    vector<int> convert(const wstring& s); //преобразование строка-вектор
    wstring convert(const vector<int>& v); //преобразование вектор-строка
    
public:
    modAlphaCipher() = delete;
    modAlphaCipher(const wstring& skey); //конструктор для установки ключа
    wstring encrypt(const wstring& open_text); //зашифрование
    wstring decrypt(const wstring& cipher_text);//расшифрование
};
