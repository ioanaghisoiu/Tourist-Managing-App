#include "VipTicket.h"

VipTicket::VipTicket(double price, std::string curr, double loungeTax_)
    : Ticket(price, std::move(curr), true), loungeTax(loungeTax_) {}

double VipTicket::getFinalPrice(int age) const {
    return Ticket::getFinalPrice(age) + loungeTax;
}

Ticket* VipTicket::clone() const {
    return new VipTicket(*this);
}

void VipTicket::print(std::ostream& os) const {
    os << "VIP: " << basePrice << " " << currency 
       << " + " << loungeTax << " " << currency << " Lounge Tax";
}