#include "Guide.h"


Guide::Guide(const std::string& name_, const std::string& surname_, int age_,
             const std::string& email_, Ticket* ticket_,
             const std::string& foreignLanguage_, int badgeNumber_)
    : Person(name_, surname_, age_, email_, ticket_), foreignLanguage(foreignLanguage_), badgeNumber(badgeNumber_) {}

Person* Guide::clone() const {
    return new Guide(*this);
}
double Guide::getTicketDiscount() const {
    return 1.0;
}

void Guide::afisare(std::ostream& os) const {
    os << name << " " << surname << " (" << age << " ani, Rol: " << getRole() 
       << ", Limba: " << foreignLanguage << ", Ecuson: " << badgeNumber <<")";
}

