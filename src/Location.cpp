#include "Location.h"

Location::Location(std::string county_, std::string address_, int siruta_)
    : county{std::move(county_)}, address{std::move(address_)}, sirutaCode{siruta_} {}

Location::Location() : county{"N/A"}, address{"N/A"}, sirutaCode{0} {}

const std::string& Location::getCounty() const { return county; }

int Location::getSirutaCode() const { return sirutaCode; }

void Location::updateAddress(const std::string& newAddress) {
    if (!newAddress.empty()) address = newAddress;
}

bool Location::operator==(const Location& other) const {
    return county == other.county && address == other.address && sirutaCode == other.sirutaCode;
}

std::ostream& operator<<(std::ostream& os, const Location& loc) {
    os << loc.address << ", jud. " << loc.county << " (Cod SIRUTA: " << loc.sirutaCode << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Location& loc) {
    std::cout << "Judet: "; is.ignore(); std::getline(is, loc.county);
    std::cout << "Adresa: "; std::getline(is, loc.address);
    std::cout << "Cod SIRUTA: "; is >> loc.sirutaCode;
    return is;
}