#pragma once
#include <iostream>
#include <string>
 
class Ticket {
private:
    double basePrice;
    std::string currency;
    bool isPriority;
public:
    explicit Ticket(double price = 0, std::string curr = "RON", bool priority = false);
    [[nodiscard]] double getFinalPrice(int age) const;
    friend std::ostream& operator<<(std::ostream& os, const Ticket& t);
    friend std::istream& operator>>(std::istream& is, Ticket& t);
};
 