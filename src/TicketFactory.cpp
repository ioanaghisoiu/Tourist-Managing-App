#include "TicketFactory.h"

Ticket* TicketFactory::createStandard(double price, const std::string& currency) {
    return new Ticket(price, currency, false);
}

Ticket* TicketFactory::createDiscount(double price, double rate, const std::string& currency) {
    return new DiscountTicket(price, currency, rate);
}

Ticket* TicketFactory::createVip(double price, double loungeTax, const std::string& currency) {
    return new VipTicket(price, currency, loungeTax);
}

Ticket* TicketFactory::createFree(const std::string& currency) {
    return new Ticket(0.0, currency, false);
}