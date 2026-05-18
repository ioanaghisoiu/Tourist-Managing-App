#include "Guide.h"


Guide::Guide(const std::string& name_, const std::string& surname_, int age_, const std::string& email_, double tPrice,
             const std::string& foreignLanguage_, int badgeNumber_)
    : Person(name_, surname_, age_, email_, tPrice),
      foreignLanguage(foreignLanguage_), badgeNumber(badgeNumber_) {}

Person* Guide::clone() const {
    return new Guide(*this);
}

void Guide::afisare(std::ostream& os) const {
    os << name << " " << surname << " (" << age << " ani, Rol: " << getRole() 
       << ", Limba: " << foreignLanguage << ", Ecuson: " << badgeNumber 
       << ", Bilet: " << ticket << ")";
}