#include "Bill.h"
#include <iostream>

int main() {
    try {
        std::cout << "Разработчик: студент группы ______, ФИО: ______\n"
                     "Задача: реализовать класс Bill (проект с Init()).\n\n";
        Bill first; // создание объекта конструктором по умолчанию
        first.Init("Иванов", "+7-900-111-22-33", 5.50, 10.0, 23, 50, 0, 20);
        first.Display();
        std::cout << "Геттер тарифа: " << first.getTariffPerMinute() << "\n";

        Bill copy; copy.Init(first); // копирование через второй Init
        copy.setDiscountPercent(20.0); copy.setPayerSurname("Петров"); copy.Display();
        Bill bills[2]; // массив объектов
        bills[0].Init(first); bills[1].Init("Сидоров", "555", 7.0, 0.0, 10, 0, 10, 15);
        std::cout << "Сравнение тарифов: first < bills[1] = " << std::boolalpha << first.tariffLessThan(bills[1]) << '\n';
        std::cout << "Результат toString(): " << first.toString() << '\n';
        // Для проверки Read() раскомментируйте следующую строку:
        // first.Read();
    } catch (const std::exception& error) { std::cerr << "Ошибка: " << error.what() << '\n'; return 1; }
    return 0;
}
