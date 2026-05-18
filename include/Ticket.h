#pragma once
#include <string>
#include <iostream>

class Ticket {
protected:
    double basePrice;
    std::string currency;
    bool isPriority;

public:
    explicit Ticket(double price = 0, std::string curr = "RON", bool priority = false);

    virtual ~Ticket() = default;

    virtual double getFinalPrice(int age) const;
    virtual Ticket* clone() const;

    friend std::ostream& operator<<(std::ostream& os, const Ticket& t) {
        t.print(os);
        return os;
    }
protected:
    virtual void print(std::ostream& os) const;
};