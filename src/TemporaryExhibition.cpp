#include "TemporaryExhibition.h"

TemporaryExhibition::TemporaryExhibition(const std::string& title_, double fee_, int items_, int daysRemaining_)
    : Exhibition(title_, fee_, items_), daysRemaining(daysRemaining_) {}

void TemporaryExhibition::print(std::ostream& os) const {
    Exhibition::print(os);
    os << " | [TEMPORARA] Zile ramase: " << daysRemaining;
}