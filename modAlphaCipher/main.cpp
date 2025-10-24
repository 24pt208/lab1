#include <iostream>
#include <locale>
#include <codecvt>
#include "modAlphaCipher.h"

// Функция для преобразования string в wstring
std::wstring string_to_wstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

// Функция для преобразования wstring в string
std::string wstring_to_string(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

void check(const std::wstring& text, const std::wstring& key)
{
    try {
        std::wstring cipherText;
        std::wstring decryptedText;
        modAlphaCipher cipher(key);
        
        cipherText = cipher.encrypt(text);
        decryptedText = cipher.decrypt(cipherText);
        
        std::wcout << L"Ключ: " << key << std::endl;
        std::wcout << L"Исходный текст: " << text << std::endl;
        std::wcout << L"Зашифрованный текст: " << cipherText << std::endl;
        std::wcout << L"Расшифрованный текст: " << decryptedText << std::endl;
        
        // Сравниваем без учета пробелов для проверки корректности шифрования
        std::wstring text_no_spaces, decrypted_no_spaces;
        for (auto c : text) if (c != L' ') text_no_spaces += c;
        for (auto c : decryptedText) if (c != L' ') decrypted_no_spaces += c;
        
        if (text_no_spaces == decrypted_no_spaces) {
            std::wcout << L"✓ Успех! Текст корректно зашифрован и расшифрован" << std::endl;
        } else {
            std::wcout << L"✗ Ошибка! Текст не совпадает после расшифровки" << std::endl;
        }
        std::wcout << L"----------------------------------------" << std::endl;
    } catch (const std::exception& e) {
        std::wcout << L"Ошибка: " << e.what() << std::endl;
        std::wcout << L"----------------------------------------" << std::endl;
    }
}

void interactive_mode()
{
    std::wstring key, text;
    unsigned op;
    
    std::wcout << L"Введите ключ: ";
    std::wcin >> key;
    
    try {
        modAlphaCipher cipher(key);
        std::wcout << L"Ключ загружен успешно!" << std::endl;
        
        do {
            std::wcout << L"\nВыберите операцию (0-выход, 1-шифрование, 2-дешифрование): ";
            std::wcin >> op;
            std::wcin.ignore(); // Игнорируем оставшийся символ новой строки
            
            if (op == 1 || op == 2) {
                std::wcout << L"Введите текст: ";
                std::getline(std::wcin, text); // Читаем всю строку с пробелами
                
                try {
                    if (op == 1) {
                        std::wstring encrypted = cipher.encrypt(text);
                        std::wcout << L"Зашифрованный текст: " << encrypted << std::endl;
                    } else {
                        std::wstring decrypted = cipher.decrypt(text);
                        std::wcout << L"Расшифрованный текст: " << decrypted << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::wcout << L"Ошибка при обработке текста: " << e.what() << std::endl;
                }
            } else if (op > 2) {
                std::wcout << L"Неверная операция!" << std::endl;
            }
        } while (op != 0);
        
    } catch (const std::exception& e) {
        std::wcout << L"Ошибка: " << e.what() << std::endl;
    }
}

int main()
{
    // Установка локали для поддержки русского языка
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
    
    std::wcout << L"=== Шифр Гронсфельда (русский язык) ===" << std::endl;
    std::wcout << L"Режим тестирования:" << std::endl;
    
    // Тестирование с различными ключами и текстами с пробелами
    check(L"ПРИВЕТ МИР", L"ЭХО");
    check(L"ПРОГРАММИРОВАНИЕ НА C++", L"КОД");
    check(L"ТЕСТОВОЕ СООБЩЕНИЕ С ПРОБЕЛАМИ", L"СЕКРЕТ");
    check(L"А Б В Г Д Е Ё Ж З", L"КЛЮЧ");
    
    std::wcout << L"\nПереход в интерактивный режим..." << std::endl;
    interactive_mode();
    
    return 0;
}
