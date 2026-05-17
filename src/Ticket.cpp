#include "Ticket.h"

Ticket::Ticket(double price, std::string curr, bool priority)
    : basePrice(price), currency(std::move(curr)), isPriority(priority) {}

double Ticket::getFinalPrice(int age) const {
    double discount = 0;
    if (age < 18) discount = 0.5;
    else if (age > 65) discount = 0.3;
    double price = basePrice * (1.0 - discount);
    if (isPriority) price += 10.0;
    return price;
}

std::ostream& operator<<(std::ostream& os, const Ticket& t) {
    os << t.basePrice << " " << t.currency << (t.isPriority ? " (Priority)" : "");
    return os;
}

std::istream& operator>>(std::istream& is, Ticket& t) {
    std::cout << "Pret bilet: "; is >> t.basePrice;
    std::cout << "Moneda: "; is >> t.currency;
    std::cout << "Priority (1/0): "; is >> t.isPriority;
    return is;
}