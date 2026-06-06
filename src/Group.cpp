#include "Group.h"
#include "Professor.h"
#include <algorithm>
#include <sstream>
#include "Student.h"
#include "Exceptions.h"
#include "Professor.h"

Group::Group(const std::string& museum_name_, long museum_code_, const Date& data_)
    : guide(nullptr), museum_code(museum_code_), museum_name(museum_name_), dataVizitei(data_) {}

Group::~Group() {
    delete guide;
    for (Person* p : members) {
        delete p;
    }
    members.clear();
}

Group::Group(const Group& other) : Countable<Group>(other), museum_code(other.museum_code), museum_name(other.museum_name), dataVizitei(other.dataVizitei){
    guide = other.guide ? other.guide->clone() : nullptr;
    for (const Person* p : other.members) {
        members.push_back(p->clone());
    }
}

Group& Group::operator=(const Group& other) {
    if (this != &other) {
        Group temp(other);
        std::swap(guide, temp.guide);
        std::swap(members, temp.members);
        std::swap(museum_code, temp.museum_code);
        std::swap(museum_name, temp.museum_name);
        std::swap(dataVizitei, temp.dataVizitei);
        std::swap(optiuneVR, temp.optiuneVR);
    }
    return *this;
}

void Group::setGuide(Person* newGuide) {
    delete guide;
    guide = newGuide;
}

bool Group::isEmailDuplicate(const std::string& email) const {
    for (const Person* p : members)
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


void Group::sortMembersByAge() {
    std::sort(members.begin(), members.end(), [](const Person* a, const Person* b) {
        return a->getAge() < b->getAge();
    });
}



bool Group::isReadyForVisit() const {
    bool ready = !members.empty() && members.size() <= 10 && museum_code != 0;

    if (ready) {
        std::stringstream ss;
        ss << "Grupul este pregatit pentru vizita.\n";
        ss << "Rezumat taxe:\n";

        double totalGeneral = 0;
        double taxaStudent = -1;
        double taxaProfesor = -1;

        for (Person* p : members) {
            double pretBilet = p->getTicketFinalPrice();
            totalGeneral += pretBilet;

            if (dynamic_cast<Student*>(p) != nullptr && taxaStudent == -1) {
                taxaStudent = pretBilet;
            }
            else if (dynamic_cast<Professor*>(p) != nullptr && taxaProfesor == -1) {
                taxaProfesor = pretBilet;
            }
        }

        if (taxaProfesor != -1) ss << " - Taxa Profesor: " << taxaProfesor << " RON/pers\n";
        if (taxaStudent != -1)  ss << " - Taxa Student: " << taxaStudent << " RON/pers\n";

        if (guide != nullptr) {
            double pretBiletGhid = guide->getTicketFinalPrice();
            double taxaServiciuGhidaj = 50.0;

            totalGeneral += pretBiletGhid + taxaServiciuGhidaj;

            ss << " - Bilet Ghid: " << pretBiletGhid << " RON\n"
               << " - Taxa serviciu ghidaj: " << taxaServiciuGhidaj << " RON (pe grup)\n";
        } else {
            ss << " - Tur liber (fara ghid)\n";
        }

        ss << "\nTotal de incasat: " << totalGeneral << " RON\n";

        for (Person* p : members) {
            const Professor* prof = dynamic_cast<Professor*>(p);
            if (prof != nullptr) {
                prof->receiveNotification(museum_name, museum_code, ss.str());
            }
        }
    }
    return ready;
}

double Group::calculateTotalRevenue() const {
    if (members.empty()) {
        throw InvalidGroupStateException();
    }

    double total = 0;
    for (const Person* p : members) {
        total += p->getTicketFinalPrice();
    }
    if (guide != nullptr) {
        total += guide->getTicketFinalPrice() + 50.0;
    }
    if (optiuneVR) total += 30.0;

    return total;
}

std::ostream& operator<<(std::ostream& os, const Group& g) {
    os << "Grup Muzeu [" << g.museum_code << "]\n";
    os << "Optiune VR: " << (g.hasVR() ? "DA" : "NU") << "\n";
    if (g.guide) {
        os << "Ghid: " << *(g.guide) << "\n";
    }
    else {
        os << "Ghid: nespecificat\n";
    }
    os << "Membri:\n";
    for (const Person* p : g.members)
        os << " - " << *p << "\n";

    return os;
}

void Group::removeMember(const std::string& emailStergere) {

    Date azi = Date::getToday();
    if (!(azi < dataVizitei)) {
        throw std::runtime_error("Politica anulare: Puteti anula doar cu cel putin o zi inainte de data vizitei!");
    }


    auto it = members.begin();
    while (it != members.end()) {
        if ((*it)->getEmail() == emailStergere) {
            delete *it;
            members.erase(it);
            return;
        }
        ++it;
    }


    throw PersonNotExistsException();
}

bool Group::areMembru(const std::string& emailCautat) const {
    for (const Person* p : members) {
        if (p->getEmail() == emailCautat) return true;
    }
    return false;
}

void Group::setDataVizitei(const Date& nouaData) {
    dataVizitei = nouaData;
}

void Group::monitorizeazaActivitateLive() const {
    std::cout << "   PANOU CONTROL: MONITORIZARE ACTIVITATE GRUP (LIVE) \n";

    for (const Person* p : members) {
        p->vizioneazaExpozitia();
    }

    if (guide!= nullptr) {
        guide->vizioneazaExpozitia();
    }
}


