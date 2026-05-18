#include "DiscountTicket.h"

DiscountTicket::DiscountTicket(double price, std::string curr, double discountRate_)
    : Ticket(price, std::move(curr), false), discountRate(discountRate_) {}

double DiscountTicket::getFinalPrice(int age) const {
    return basePrice * (1.0 - discountRate);
}

Ticket* DiscountTicket::clone() const {
    return new DiscountTicket(*this);
}

void DiscountTicket::print(std::ostream& os) const {
    os << "REDUCERE: " << basePrice << " " << currency 
       << " (-" << (discountRate * 100) << "%)";
}