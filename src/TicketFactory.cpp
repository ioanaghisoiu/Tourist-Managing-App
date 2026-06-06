#include "TicketFactory.h"

Ticket* TicketFactory::createStandard(double price, const std::string& currency) {
    StandardPricingStrategy strategy;
    return new Ticket(strategy.calculatePrice(price), currency, false);
}

Ticket* TicketFactory::createDiscount(double price, double rate, const std::string& currency) {
    DiscountPricingStrategy strategy(rate);
    return new Ticket(strategy.calculatePrice(price), currency, false);
}

Ticket* TicketFactory::createFree(const std::string& currency) {
    FreePricingStrategy strategy;
    return new Ticket(strategy.calculatePrice(0.0), currency, false);
}