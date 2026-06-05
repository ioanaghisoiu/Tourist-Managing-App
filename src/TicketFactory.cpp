#include "TicketFactory.h"

Ticket* TicketFactory::createStandard(double price, const std::string& currency) {
    return new Ticket(price, currency, false);
}

Ticket* TicketFactory::createDiscount(double price, double rate, const std::string& currency) {
    return new DiscountTicket(price, currency, rate);
}

Ticket* TicketFactory::createFree(const std::string& currency) {
    return new Ticket(0.0, currency, false);
}