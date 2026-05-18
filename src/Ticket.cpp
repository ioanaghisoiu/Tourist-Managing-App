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

Ticket* Ticket::clone() const {
    return new Ticket(*this);
}

void Ticket::print(std::ostream& os) const {
    os << basePrice << " " << currency << (isPriority ? " (Priority)" : " (Standard)");
}