#pragma once

#include <string>

// Первый проект: класс инициализируется методами Init().
class Bill {
private:
    std::string payerSurname_;
    std::string phoneNumber_;
    double tariffPerMinute_;
    double discountPercent_;
    int startHour_;
    int startMinute_;
    int endHour_;
    int endMinute_;

    static void validateTime(int hour, int minute);
    static void validateText(const std::string& value, const char* fieldName);
    static void validateMoney(double value, const char* fieldName);
    static void validateDiscount(double value);

public:
    Bill() noexcept;

    // Init с отдельными значениями полей.
    void Init(const std::string& payerSurname, const std::string& phoneNumber,
              double tariffPerMinute, double discountPercent,
              int startHour, int startMinute, int endHour, int endMinute);
    // Init копированием другого объекта того же класса.
    void Init(const Bill& other) noexcept;

    void Read();
    void Display() const;
    std::string toString() const;

    const std::string& getPayerSurname() const noexcept;
    const std::string& getPhoneNumber() const noexcept;
    double getTariffPerMinute() const noexcept;
    double getDiscountPercent() const noexcept;
    int getStartHour() const noexcept;
    int getStartMinute() const noexcept;
    int getEndHour() const noexcept;
    int getEndMinute() const noexcept;

    void setPayerSurname(const std::string& value);
    void setPhoneNumber(const std::string& value);
    void setTariffPerMinute(double value);
    void setDiscountPercent(double value);
    void setStartTime(int hour, int minute);
    void setEndTime(int hour, int minute);

    int durationMinutes() const noexcept;
    double discountAmount() const noexcept;
    double paymentAmount() const noexcept;

    bool tariffLessThan(const Bill& other) const noexcept;
    bool tariffEqualTo(const Bill& other) const noexcept;
};
