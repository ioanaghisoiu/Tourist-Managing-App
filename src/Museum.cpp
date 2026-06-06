#include "Museum.h"
#include "Exceptions.h"
#include <algorithm>
#include <iostream>
int Museum::totalMuseumsCreated = 0;

Museum::Museum(std::string name_, long code_, Location loc_)
    : name{std::move(name_)}, code{code_}, location{std::move(loc_)}, totalRevenue(0.0) {
    totalMuseumsCreated++;
}

Museum::~Museum() {
    for (Exhibition* ex : exhibitions) delete ex;
}

int Museum::getTotalMuseums() { return totalMuseumsCreated; }
void Museum::addExhibition(Exhibition* ex) { exhibitions.push_back(ex); }

bool Museum::hasExhibition(const std::string& searchTitle) const {
    return std::any_of(exhibitions.begin(), exhibitions.end(),
        [&](const Exhibition* ex) { return ex->getTitle() == searchTitle; });
}

int Museum::totalItems() const {
    int total = 0;
    for (const Exhibition* ex : exhibitions) total += ex->getItemsCount();
    return total;
}


long Museum::getCode() const { return code; }
const std::string& Museum::getName() const { return name; }

double Museum::getTotalRevenue() const {
    return totalRevenue;
}

void Museum::hostGroupVisit(const Group& g) {
    if (g.getMuseumCode() != this->code) {
        throw WrongMuseumException();
    }

    double baniIncasati = g.calculateTotalRevenue();
    this->totalRevenue += baniIncasati;

    std::cout << "Vizita acceptata! Muzeul " << this->name
              << " a incasat " << baniIncasati << " RON de la acest grup.\n";
}

std::ostream& operator<<(std::ostream& os, const Museum& m) {
    os << "MUZEU: " << m.name << " [Cod: " << m.code << "]\n"
       << "Locatie: " << m.location << "\n"
       << "Total exponate: " << m.totalItems() << "\nExpozitii:\n";
   for (const Exhibition* e : m.exhibitions) os << *e << "\n";
    return os;
}