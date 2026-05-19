#include "InteractiveExhibition.h"

InteractiveExhibition::InteractiveExhibition(const std::string& title_, double fee_, int items_, const std::string& deviceType_)
    : Exhibition(title_, fee_, items_), deviceType(deviceType_) {}

void InteractiveExhibition::print(std::ostream& os) const {
    Exhibition::print(os);
    os << " | [INTERACTIVA] Echipament: " << deviceType;
}

void InteractiveExhibition::interact() const {
    std::cout << " Echipamentele de tip \"" << deviceType
              << "\" au fost deblocate cu succes pentru vizitatori la expozitia \"" << title << "\".\n";
}