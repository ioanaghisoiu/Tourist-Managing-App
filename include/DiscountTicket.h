#pragma once
#include "Ticket.h"

class DiscountTicket : public Ticket {
private:
    double discountRate;

public:
    DiscountTicket(double price, std::string curr, double discountRate_);
    
    double getFinalPrice(int age) const override;
    Ticket* clone() const override;

protected:
    void print(std::ostream& os) const override;
};