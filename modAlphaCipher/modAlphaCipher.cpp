#include "modAlphaCipher.h"
#include <algorithm>

modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(getValidKey(skey));
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::wstring valid_text = getValidText(open_text, true);
    std::vector<int> work = convert(valid_text);
    
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::wstring valid_text = getValidText(cipher_text, false);
    std::vector<int> work = convert(valid_text);
    
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (auto c : s) {
        if (alphaNum.find(c) != alphaNum.end()) {
            result.push_back(alphaNum[c]);
        }
    }
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (auto i : v) {
        if (i >= 0 && i < numAlpha.size()) {
            result.push_back(numAlpha[i]);
        }
    }
    return result;
}

std::wstring modAlphaCipher::getValidKey(const std::wstring& s)
{
    if (s.empty()) {
        throw std::invalid_argument("Пустой ключ");
    }
    
    std::wstring tmp;
    for (auto c : s) {
        if (iswalpha(c)) {
            if (iswlower(c)) {
                tmp.push_back(towupper(c));
            } else {
                tmp.push_back(c);
            }
        }
    }
    
    if (tmp.empty()) {
        throw std::invalid_argument("Ключ не содержит букв");
    }
    
    return tmp;
}

std::wstring modAlphaCipher::getValidText(const std::wstring& s, bool isEncrypt)
{
    if (s.empty()) {
        throw std::invalid_argument("Пустой текст");
    }
    
    if (isEncrypt) {
        // Для шифрования: сохраняем пробелы, обрабатываем только буквы
        std::wstring result;
        for (auto c : s) {
            if (iswalpha(c)) {
                if (iswlower(c)) {
                    result.push_back(towupper(c));
                } else {
                    result.push_back(c);
                }
            } else if (c == L' ') {
                result.push_back(c); // Сохраняем пробелы
            }
            // Остальные символы игнорируем
        }
        
        if (result.empty()) {
            throw std::invalid_argument("Текст не содержит букв");
        }
        
        return result;
    } else {
        // Для дешифрования: проверяем, что текст содержит только буквы и пробелы
        for (auto c : s) {
            if (!iswalpha(c) && c != L' ') {
                throw std::invalid_argument("Зашифрованный текст содержит недопустимые символы");
            }
        }
        return s;
    }
}
