#pragma once
#include <string>
#include "Ticket.h"
#include "DiscountTicket.h"
#include "IPricingStrategy.h"

class TicketFactory {
public:
    static Ticket* createStandard(double price, const std::string& currency = "RON");
    static Ticket* createDiscount(double price, double rate, const std::string& currency = "RON");
    static Ticket* createFree(const std::string& currency = "RON");
};