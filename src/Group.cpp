#include "Group.h"

Group::Group(const std::vector<Person>& persons_, const Person& guide_, long museum_code_)
    : persons(persons_), guide(guide_), museum_code(museum_code_) {
    guide.validateEmail();
}

bool Group::isEmailDuplicate(const std::string& email) const {
    for (const auto& p : persons)
        if (p.getEmail() == email) return true;
    return false;
}

void Group::addMember(const Person& member) {
    if (persons.size() >= 10) throw GroupThresholdException();
    if (isEmailDuplicate(member.getEmail())) {
        std::cout << "Eroare: Email duplicat: " << member.getEmail() << "\n";
        return;
    }
    persons.push_back(member);
}

double Group::calculateAverageAge() const {
    if (persons.empty()) return 0.0;
    double sum = 0;
    for (const auto& p : persons) sum += p.getAge();
    return sum / (double)persons.size();
}

bool Group::isReadyForVisit() const {
    return !persons.empty() && persons.size() <= 10
           && guide.getAge() >= 18 && museum_code != 0;
}

double Group::calculateTotalRevenue() const {
    double total = 0;
    for (const auto& p : persons) {
        if (p.getAge() < 18) total += 10.0;
        else if (p.getAge() > 65) total += 15.0;
        else total += 25.0;
    }
    return total;
}

std::ostream& operator<<(std::ostream& os, const Group& g) {
    os << "Grup Muzeu [" << g.museum_code << "]\nGhid: " << g.guide << "\nMembri:\n";
    for (const auto& p : g.persons) os << " - " << p << "\n";
    return os;
}