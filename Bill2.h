#pragma once
#include <string>

// Второй проект: вместо Init() используются конструкторы.
class Bill {
private:
    std::string surname_, phone_;
    double tariff_, discount_;
    int startHour_, startMinute_, endHour_, endMinute_;
    static void checkTime(int h, int m);
    static void checkText(const std::string& value, const char* name);
    static void checkValues(double tariff, double discount);
public:
    Bill() noexcept;
    Bill(const std::string& surname, const std::string& phone, double tariff, double discount,
         int startHour, int startMinute, int endHour, int endMinute);
    Bill(const Bill& other) = default;

    void Read();
    void Display() const;
    std::string toString() const;
    const std::string& getSurname() const noexcept;
    const std::string& getPhone() const noexcept;
    double getTariff() const noexcept;
    double getDiscount() const noexcept;
    void setSurname(const std::string& value);
    void setPhone(const std::string& value);
    void setTariff(double value);
    void setDiscount(double value);
    void setStartTime(int h, int m);
    void setEndTime(int h, int m);
    int durationMinutes() const noexcept;
    double discountAmount() const noexcept;
    double paymentAmount() const noexcept;
    bool tariffLessThan(const Bill& other) const noexcept;
    bool tariffEqualTo(const Bill& other) const noexcept;
};
