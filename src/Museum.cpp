#include "Museum.h"

int Museum::totalMuseumsCreated = 0;

Museum::Museum(std::string name_, long code_, Location loc_)
    : name{std::move(name_)}, code{code_}, location{std::move(loc_)} {
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

std::ostream& operator<<(std::ostream& os, const Museum& m) {
    os << "MUZEU: " << m.name << " [Cod: " << m.code << "]\n"
       << "Locatie: " << m.location << "\n"
       << "Total exponate: " << m.totalItems() << "\nExpozitii:\n";
    for (const auto& e : m.exhibitions) os << e << "\n";
    return os;
}