#include "Museum.h"
#include "Exceptions.h"
#include <algorithm>
#include <iostream>
int Museum::totalMuseumsCreated = 0;

Museum::Museum(std::string name_, long code_, Location loc_)
    : name{std::move(name_)}, code{code_}, location{std::move(loc_)}, totalRevenue(0.0) {
    totalMuseumsCreated++;
}

int Museum::getTotalMuseums() { return totalMuseumsCreated; }
void Museum::addExhibition(const Exhibition& ex) { exhibitions.push_back(ex); }
void Museum::addVote(int score) { popularityVotes.push_back(score); }

bool Museum::hasExhibition(const std::string& searchTitle) const {
    return std::any_of(exhibitions.begin(), exhibitions.end(),
        [&](const Exhibition& ex) { return ex.getTitle() == searchTitle; });
}

int Museum::totalItems() const {
    int total = 0;
    for (const auto& ex : exhibitions) total += ex.getItemsCount();
    return total;
}

double Museum::averageVote() const {
    if (popularityVotes.empty()) return 0.0;
    double sum = 0;
    for (int v : popularityVotes) sum += v;
    return sum / popularityVotes.size();
}

long Museum::getCode() const { return code; }
const std::string& Museum::getName() const { return name; }

double Museum::getTotalRevenue() const {
    return totalRevenue;
}

void Museum::hostGroupVisit(Group& g) {
    if (g.getMuseumCode() != this->code) {
        throw WrongMuseumException();
    }

    double baniIncasati = g.calculateTotalRevenue();
    this->totalRevenue += baniIncasati;

    std::cout << "Vizita acceptata! Muzeul " << this->name
              << " a incasat " << baniIncasati << " RON de la acest grup.\n";
}

std::vector<Exhibition> Museum::getAffordableExhibitions(double maxBudget) const {
    std::vector<Exhibition> affordable;
    std::copy_if(exhibitions.begin(), exhibitions.end(), std::back_inserter(affordable),
                 [maxBudget](const Exhibition& ex) {
                     return ex.getExtraFee() <= maxBudget;
                 });
    return affordable;
}

std::ostream& operator<<(std::ostream& os, const Museum& m) {
    os << "MUZEU: " << m.name << " [Cod: " << m.code << "]\n"
       << "Locatie: " << m.location << "\n"
       << "Total exponate: " << m.totalItems() << "\nExpozitii:\n";
    for (const auto& e : m.exhibitions) os << e << "\n";
    return os;
}