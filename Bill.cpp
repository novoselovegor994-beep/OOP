#include "Bill.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

Bill::Bill() noexcept : tariffPerMinute_(0.0), discountPercent_(0.0),
    startHour_(0), startMinute_(0), endHour_(0), endMinute_(0) {}

void Bill::validateTime(int hour, int minute) {
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        throw std::invalid_argument("Время должно быть в диапазоне 00:00..23:59");
    }
}

void Bill::validateText(const std::string& value, const char* fieldName) {
    if (value.empty()) throw std::invalid_argument(std::string(fieldName) + " не может быть пустым");
}

void Bill::validateMoney(double value, const char* fieldName) {
    if (!std::isfinite(value) || value < 0.0) throw std::invalid_argument(std::string(fieldName) + " должно быть неотрицательным числом");
}

void Bill::validateDiscount(double value) {
    if (!std::isfinite(value) || value < 0.0 || value > 100.0) throw std::invalid_argument("Скидка должна быть в диапазоне 0..100 процентов");
}

void Bill::Init(const std::string& surname, const std::string& phone, double tariff, double discount,
                int startHour, int startMinute, int endHour, int endMinute) {
    validateText(surname, "Фамилия"); validateText(phone, "Номер телефона");
    validateMoney(tariff, "Тариф"); validateDiscount(discount);
    validateTime(startHour, startMinute); validateTime(endHour, endMinute);
    payerSurname_ = surname; phoneNumber_ = phone; tariffPerMinute_ = tariff;
    discountPercent_ = discount; startHour_ = startHour; startMinute_ = startMinute;
    endHour_ = endHour; endMinute_ = endMinute;
}

void Bill::Init(const Bill& other) noexcept { *this = other; }

void Bill::Read() {
    std::string surname, phone; double tariff, discount; int sh, sm, eh, em;
    std::cout << "Фамилия: "; if (!(std::cin >> surname)) throw std::invalid_argument("Ошибка ввода фамилии");
    std::cout << "Номер телефона: "; if (!(std::cin >> phone)) throw std::invalid_argument("Ошибка ввода номера");
    std::cout << "Тариф за минуту: "; if (!(std::cin >> tariff)) throw std::invalid_argument("Ошибка ввода тарифа");
    std::cout << "Скидка (%): "; if (!(std::cin >> discount)) throw std::invalid_argument("Ошибка ввода скидки");
    std::cout << "Начало (часы минуты): "; if (!(std::cin >> sh >> sm)) throw std::invalid_argument("Ошибка ввода времени начала");
    std::cout << "Окончание (часы минуты): "; if (!(std::cin >> eh >> em)) throw std::invalid_argument("Ошибка ввода времени окончания");
    Init(surname, phone, tariff, discount, sh, sm, eh, em);
}

void Bill::Display() const { std::cout << toString() << '\n'; }

std::string Bill::toString() const {
    std::ostringstream out; out << std::fixed << std::setprecision(2)
        << "Плательщик: " << payerSurname_ << ", телефон: " << phoneNumber_
        << ", время: " << std::setw(2) << std::setfill('0') << startHour_ << ':' << std::setw(2) << startMinute_
        << "-" << std::setw(2) << endHour_ << ':' << std::setw(2) << endMinute_ << std::setfill(' ')
        << ", тариф: " << tariffPerMinute_ << ", скидка: " << discountPercent_ << "%"
        << ", длительность: " << durationMinutes() << " мин., скидка: " << discountAmount()
        << ", к оплате: " << paymentAmount(); return out.str();
}

const std::string& Bill::getPayerSurname() const noexcept { return payerSurname_; }
const std::string& Bill::getPhoneNumber() const noexcept { return phoneNumber_; }
double Bill::getTariffPerMinute() const noexcept { return tariffPerMinute_; }
double Bill::getDiscountPercent() const noexcept { return discountPercent_; }
int Bill::getStartHour() const noexcept { return startHour_; }
int Bill::getStartMinute() const noexcept { return startMinute_; }
int Bill::getEndHour() const noexcept { return endHour_; }
int Bill::getEndMinute() const noexcept { return endMinute_; }
void Bill::setPayerSurname(const std::string& v) { validateText(v, "Фамилия"); payerSurname_ = v; }
void Bill::setPhoneNumber(const std::string& v) { validateText(v, "Номер телефона"); phoneNumber_ = v; }
void Bill::setTariffPerMinute(double v) { validateMoney(v, "Тариф"); tariffPerMinute_ = v; }
void Bill::setDiscountPercent(double v) { validateDiscount(v); discountPercent_ = v; }
void Bill::setStartTime(int h, int m) { validateTime(h, m); startHour_ = h; startMinute_ = m; }
void Bill::setEndTime(int h, int m) { validateTime(h, m); endHour_ = h; endMinute_ = m; }

int Bill::durationMinutes() const noexcept {
    int start = startHour_ * 60 + startMinute_, end = endHour_ * 60 + endMinute_;
    int result = (end - start + 24 * 60) % (24 * 60); return result == 0 ? 0 : result;
}
double Bill::discountAmount() const noexcept { return durationMinutes() * tariffPerMinute_ * discountPercent_ / 100.0; }
double Bill::paymentAmount() const noexcept { return durationMinutes() * tariffPerMinute_ - discountAmount(); }
bool Bill::tariffLessThan(const Bill& other) const noexcept { return tariffPerMinute_ < other.tariffPerMinute_; }
bool Bill::tariffEqualTo(const Bill& other) const noexcept { return tariffPerMinute_ == other.tariffPerMinute_; }
