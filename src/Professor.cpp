#include "Professor.h"

Professor::Professor(const std::string& name_, const std::string& surname_, int age_,
                     const std::string& email_, Ticket* ticket_,
                     int experience_, const std::string& school_)
    : Person(name_, surname_, age_, email_, ticket_), experience(experience_), school(school_) {}

Person* Professor::clone() const {
    return new Professor(*this);
}

void Professor::afisare(std::ostream& os) const {
    os << name << " " << surname << " (" << age << " ani, Rol: " << getRole()
       << ", Experienta: " << experience << " ani, Scoala: " << school<< ")";
}

void Professor::receiveNotification(const std::string& museumName, long museumCode, const std::string& message) const {
    std::cout << "Notificare primita de Profesorul " << name << " " << surname
              << " pentru muzeul " << museumName << " [" << museumCode << "]: " << message << "\n";
}

void Professor::vizioneazaExpozitia() const {
    std::cout << "Profesorul " << name << " " << surname
              << " le explica elevilor legatura dintre exponate si materia de la clasa.\n";
}

void Professor::onNotificare(const std::string& mesaj) {
    mesajePrimite.push_back(mesaj);
}

const std::vector<std::string>& Professor::getMesaje() const {
    return mesajePrimite;
}