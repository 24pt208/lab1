#include <iostream>
#include <string>
#include "module.h"

void demonstrationMode()
{
    std::cout << "=== РЕЖИМ ДЕМОНСТРАЦИИ ===" << std::endl;
    
    try {
        // Тест 1
        routeCipher cipher1(3);
        std::string text1 = "HELLOWORLD";
        std::string encrypted1 = cipher1.encrypt(text1);
        std::string decrypted1 = cipher1.decrypt(encrypted1);
        
        std::cout << "Ключ: 3" << std::endl;
        std::cout << "Исходный текст: " << text1 << std::endl;
        std::cout << "Зашифрованный: " << encrypted1 << std::endl;
        std::cout << "Расшифрованный: " << decrypted1 << std::endl;
        std::cout << "Статус: " << (text1 == decrypted1 ? "УСПЕХ" : "ОШИБКА") << std::endl;
        std::cout << std::endl;
        
        // Тест 2
        routeCipher cipher2(4);
        std::string text2 = "PROGRAMMING";
        std::string encrypted2 = cipher2.encrypt(text2);
        std::string decrypted2 = cipher2.decrypt(encrypted2);
        
        std::cout << "Ключ: 4" << std::endl;
        std::cout << "Исходный текст: " << text2 << std::endl;
        std::cout << "Зашифрованный: " << encrypted2 << std::endl;
        std::cout << "Расшифрованный: " << decrypted2 << std::endl;
        std::cout << "Статус: " << (text2 == decrypted2 ? "УСПЕХ" : "ОШИБКА") << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void interactiveMode()
{
    std::cout << "\n=== ИНТЕРАКТИВНЫЙ РЕЖИМ ===" << std::endl;
    
    int key;
    std::cout << "Введите ключ (количество столбцов): ";
    std::cin >> key;
    std::cin.ignore(); // Очистка буфера
    
    try {
        routeCipher cipher(key);
        
        int choice;
        do {
            std::cout << "\nВыберите операцию:\n";
            std::cout << "1 - Зашифровать текст\n";
            std::cout << "2 - Расшифровать текст\n";
            std::cout << "0 - Выход\n";
            std::cout << "Ваш выбор: ";
            std::cin >> choice;
            std::cin.ignore();
            
            if (choice == 1 || choice == 2) {
                std::string text;
                std::cout << "Введите текст: ";
                std::getline(std::cin, text);
                
                try {
                    if (choice == 1) {
                        std::string encrypted = cipher.encrypt(text);
                        std::cout << "Зашифрованный текст: " << encrypted << std::endl;
                    } else {
                        std::string decrypted = cipher.decrypt(text);
                        std::cout << "Расшифрованный текст: " << decrypted << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cout << "Ошибка обработки: " << e.what() << std::endl;
                }
            } else if (choice != 0) {
                std::cout << "Неверный выбор!" << std::endl;
            }
            
        } while (choice != 0);
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка инициализации: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "ШИФР ТАБЛИЧНОЙ МАРШРУТНОЙ ПЕРЕСТАНОВКИ" << std::endl;
    std::cout << "======================================" << std::endl;
    
    demonstrationMode();
    interactiveMode();
    
    std::cout << "\nПрограмма завершена." << std::endl;
    return 0;
}
