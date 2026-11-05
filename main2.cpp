#include "Bill.h"
#include <iostream>

int main() {
    try {
        std::cout << "Разработчик: студент группы ______, ФИО: ______\nЗадача: реализовать класс Bill (проект с конструкторами).\n\n";
        Bill first; // Создание объекта конструктором по умолчанию.
        Bill second("Иванов", "+7-900-111-22-33", 5.50, 10, 23, 50, 0, 20); // Конструктор с параметрами.
        Bill copy(second); // Конструктор копирования.
        Bill bills[2]{second, Bill("Сидоров", "555", 7, 0, 10, 0, 10, 15)}; // Массив объектов и временный объект.
        first = copy; first.setDiscount(20); first.setSurname("Петров");
        first.Display(); bills[1].Display();
        std::cout << "Геттер тарифа: " << first.getTariff() << "\nСравнение тарифов: " << std::boolalpha << first.tariffLessThan(bills[1]) << "\n";
        std::cout << "Результат toString(): " << first.toString() << '\n';
        // Для проверки Read() раскомментируйте: first.Read(); first.Display();
    } catch (const std::exception& error) { std::cerr << "Ошибка: " << error.what() << '\n'; return 1; }
    return 0;
}
