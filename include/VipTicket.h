#pragma once
#include "Ticket.h"

class VipTicket : public Ticket {
private:
    double loungeTax;

public:
    VipTicket(double price, std::string curr, double loungeTax_);
    
    double getFinalPrice(int age) const override;
    Ticket* clone() const override;

protected:
    void print(std::ostream& os) const override;
};