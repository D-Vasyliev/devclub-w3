#include <iostream>

class InvalidDateException {};

class Date {
private:
    int day;
    int month;
    int year;

    const int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    bool isLeapYear(int year) const {     // Перевірка, чи є рік високосним
         return year % 4 == 0 || (year % 100 == 0 && year % 400 == 0);
    }

    int getDaysInMonth(int month, int year) const { // Отримання кількості днів у місяці з урахуванням високосного року
        int days = daysInMonth[month - 1];

        if (month == 2 && isLeapYear(year)) // Якщо лютий і високосний рік, додаємо один день
            days += 1;

        return days;
    }

    void validate(int day, int month, int year) {
        if (year <= 0)
            throw InvalidDateException();
        if (month <= 0 || month > 12)
            throw InvalidDateException();
        if (day <= 0 || day > getDaysInMonth(month, year))
            throw InvalidDateException();
    }

    long toSerialNumber() const {
        long totalDays = 365 * (year - 1) + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;

        for(int m = 1; m < month; m++) {
            totalDays += getDaysInMonth(m, year);
        }

        totalDays += day;

        return totalDays;
    }

public:
    Date(int day=1, int month=1, int year=1970) {
        validate(day, month, year);
        this->day = day;
        this->month = month;
        this->year = year;
    }

    int getDay() const { return this->day; }
    int getMonth() const { return this->month; }
    int getYear() const { return this->year; }

    long operator-(const Date& other) const {
        return this->toSerialNumber() - other.toSerialNumber();
    }

    friend std::ostream& operator<<(std::ostream& out, const Date& date);
};

std::ostream& operator<<(std::ostream& out, const Date& date) {
    if (date.day < 10) out << '0';
    out << date.day << '.';
    if (date.month < 10) out << '0';
    out << date.month << '.';
    out << date.year;
    return out;
}

int main() {
    try {
        Date start(01, 1, 2024);
        Date current(19, 9, 2024);
        long days = current - start;

        std::cout << "Start Date: " << start << std::endl;     // 24.02.2022
        std::cout << "Current Date: " << current << std::endl; // 19.09.2024
        std::cout << "Difference in days: " << days << std::endl; // 938

    } catch (InvalidDateException& exc) {
        std::cout << "Date Error" << std::endl;
    }

    return 0;
}
