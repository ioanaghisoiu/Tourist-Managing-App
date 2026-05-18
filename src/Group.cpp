#include "Group.h"
#include "Professor.h"
#include <algorithm>

Group::Group(const std::string& museum_name_, long museum_code_)
    : guide(nullptr), museum_name(museum_name_), museum_code(museum_code_) {}

Group::~Group() {
    delete guide;
    for (Person* p : members) {
        delete p;
    }
    members.clear();
}

Group::Group(const Group& other) : museum_code(other.museum_code) {
    guide = other.guide ? other.guide->clone() : nullptr;
    for (Person* p : other.members) {
        members.push_back(p->clone());
    }
}

Group& Group::operator=(const Group& other) {
    if (this != &other) {
        Group temp(other);
        std::swap(guide, temp.guide);
        std::swap(members, temp.members);
        std::swap(museum_code, temp.museum_code);
    }
    return *this;
}

void Group::setGuide(Person* newGuide) {
    delete guide;
    guide = newGuide;
}

bool Group::isEmailDuplicate(const std::string& email) const {
    for (Person* p : members)
        if (p->getEmail() == email) return true;
    return false;
}


void Group::addMember(Person* member) {
    if (members.size() >= 10) {
        delete member;
        throw GroupThresholdException();
    }
    if (isEmailDuplicate(member->getEmail())) {
        {
            delete member;
            throw DuplicateEmailException();
        }
    }
    members.push_back(member);
}

double Group::calculateAverageAge() const {
    if (members.empty()) return 0.0;
    double sum = 0;
    for (const auto& p : members) sum += p->getAge();
    return sum / (double)members.size();
}
void Group::sortMembersByAge() {
    std::sort(members.begin(), members.end(), [](Person* a, Person* b) {
        return a->getAge() < b->getAge();
    });
}

int Group::countMinors() const {
    return std::count_if(members.begin(), members.end(), [](Person* p) {
        return p->isMinor();
    });
}

bool Group::isReadyForVisit() const {
    bool ready = !members.empty() && members.size() <= 10
           && guide->getAge() >= 18 && museum_code != 0;
    if (ready) {
        for (Person* p : members) {
            Professor* prof= dynamic_cast<Professor*>(p);
            if (prof!=nullptr) {
                prof->receiveNotification(museum_name, museum_code,
                    "Grupul dumneavoastra este complet si pregatit pentru vizita!");
            }
        }
    }
    return ready;
}

double Group::calculateTotalRevenue() const {
    if (!isReadyForVisit())
        throw InvalidGroupStateException();
    double total = 0;
    for (Person* p : members) {
        total += 25.0 * (1.0 - p->getTicketDiscount());
    }
    return total;
}

std::ostream& operator<<(std::ostream& os, const Group& g) {
    os << "Grup Muzeu [" << g.museum_code << "]\n";
    if (g.guide) {
        os << "Ghid: " << *(g.guide) << "\n";
    }
    else {
        os << "Ghid: nespecificat\n";
    }
    os << "Membri:\n";
    for (Person* p : g.members)
        os << " - " << *p << "\n";

    return os;
}