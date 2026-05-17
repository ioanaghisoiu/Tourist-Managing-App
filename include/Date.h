#pragma once
#include <iostream>
#include <chrono>
 
class Date {
private:
    std::chrono::year_month_day ymd;
public:
    explicit Date(int d = 1, int m = 1, int y = 2024);
    bool isValid() const;
    bool operator==(const Date& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Date& dt);
    friend std::istream& operator>>(std::istream& is, Date& dt);
};