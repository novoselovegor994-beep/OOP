#include "Bill.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

// Нулевой объект удобен для последующего заполнения через Read() или setters.
Bill::Bill() noexcept : tariff_(0), discount_(0), startHour_(0), startMinute_(0), endHour_(0), endMinute_(0) {}
void Bill::checkTime(int h, int m) { if (h < 0 || h > 23 || m < 0 || m > 59) throw std::invalid_argument("Неверное время"); }
void Bill::checkText(const std::string& v, const char* n) { if (v.empty()) throw std::invalid_argument(std::string(n) + " не может быть пустым"); }
void Bill::checkValues(double t, double d) { if (!std::isfinite(t) || t < 0 || !std::isfinite(d) || d < 0 || d > 100) throw std::invalid_argument("Неверный тариф или скидка"); }
Bill::Bill(const std::string& s, const std::string& p, double t, double d, int sh, int sm, int eh, int em)
    : surname_(s), phone_(p), tariff_(t), discount_(d), startHour_(sh), startMinute_(sm), endHour_(eh), endMinute_(em) {
    checkText(s, "Фамилия"); checkText(p, "Номер телефона"); checkValues(t, d); checkTime(sh, sm); checkTime(eh, em);
}
void Bill::Read() {
    std::string s, p; double t, d; int sh, sm, eh, em;
    std::cout << "Фамилия, телефон, тариф, скидка, начало(ч м), окончание(ч м): ";
    if (!(std::cin >> s >> p >> t >> d >> sh >> sm >> eh >> em)) throw std::invalid_argument("Ошибка ввода");
    checkText(s, "Фамилия"); checkText(p, "Номер телефона"); checkValues(t, d); checkTime(sh, sm); checkTime(eh, em);
    surname_ = s; phone_ = p; tariff_ = t; discount_ = d; startHour_ = sh; startMinute_ = sm; endHour_ = eh; endMinute_ = em;
}
void Bill::Display() const { std::cout << toString() << '\n'; }
std::string Bill::toString() const { std::ostringstream o; o << std::fixed << std::setprecision(2) << "Плательщик: " << surname_ << ", телефон: " << phone_ << ", время: " << startHour_ << ':' << startMinute_ << '-' << endHour_ << ':' << endMinute_ << ", тариф: " << tariff_ << ", скидка: " << discount_ << "%, длительность: " << durationMinutes() << " мин., к оплате: " << paymentAmount(); return o.str(); }
const std::string& Bill::getSurname() const noexcept { return surname_; }
const std::string& Bill::getPhone() const noexcept { return phone_; }
double Bill::getTariff() const noexcept { return tariff_; }
double Bill::getDiscount() const noexcept { return discount_; }
void Bill::setSurname(const std::string& v) { checkText(v, "Фамилия"); surname_ = v; }
void Bill::setPhone(const std::string& v) { checkText(v, "Номер телефона"); phone_ = v; }
void Bill::setTariff(double v) { checkValues(v, discount_); tariff_ = v; }
void Bill::setDiscount(double v) { checkValues(tariff_, v); discount_ = v; }
void Bill::setStartTime(int h, int m) { checkTime(h, m); startHour_ = h; startMinute_ = m; }
void Bill::setEndTime(int h, int m) { checkTime(h, m); endHour_ = h; endMinute_ = m; }
// Разность по модулю суток позволяет корректно считать звонок через полночь.
int Bill::durationMinutes() const noexcept { int a = startHour_ * 60 + startMinute_, b = endHour_ * 60 + endMinute_; return (b - a + 1440) % 1440; }
double Bill::discountAmount() const noexcept { return durationMinutes() * tariff_ * discount_ / 100; }
double Bill::paymentAmount() const noexcept { return durationMinutes() * tariff_ - discountAmount(); }
bool Bill::tariffLessThan(const Bill& o) const noexcept { return tariff_ < o.tariff_; }
bool Bill::tariffEqualTo(const Bill& o) const noexcept { return tariff_ == o.tariff_; }
