#include "Person.h"

Person::Person(const std::string& name_, const std::string& surname_, int age_,
               const std::string& email_,Ticket* ticket_)
    : name(name_), surname(surname_), age(age_), email(email_), ticket(ticket_) {}


Person::~Person() {
    delete ticket;
}

Person::Person(const Person& other)
    : name(other.name), surname(other.surname), age(other.age), email(other.email) {
    ticket = (other.ticket != nullptr) ? other.ticket->clone() : nullptr;
}


Person& Person::operator=(const Person& other) {
    if (this != &other) {
        name = other.name;
        surname = other.surname;
        age = other.age;
        email = other.email;

        delete ticket;
        ticket = (other.ticket != nullptr) ? other.ticket->clone() : nullptr;
    }
    return *this;
}

void Person::afisareBilete(std::ostream& os) const {
    if (ticket != nullptr) {
        os << ", Bilet: [" << *ticket << "]";
    } else {
        os << ", [Fara bilet]";
    }
}

void Person::validateEmail() const {
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.');
    if (atPos == std::string::npos || dotPos == std::string::npos
        || atPos == 0 || atPos == email.length() - 1) {
        std::cout << "Avertisment: Format email invalid pentru " << name << "\n";
        return;
        }
    std::cout << "Email validat pentru " << name << ".\n";
}

const std::string& Person::getName() const { return name; }
const std::string& Person::getEmail() const { return email; }
int Person::getAge() const { return age; }
void Person::setName(const std::string& n) { name = n; }
void Person::setSurname(const std::string& s) { surname = s; }
void Person::setEmail(const std::string& e) { email = e; validateEmail(); }
void Person::setAge(int a) { if (a >= 0) age = a; }
bool Person::isMinor() const { return age < 18; }

bool Person::operator==(const Person& other) const {
    return name == other.name && surname == other.surname
           && age == other.age && email == other.email;
}
bool Person::operator!=(const Person& other) const { return !(*this == other); }
bool Person::operator<(const Person& other) const { return age < other.age; }

void Person::afisare(std::ostream& os) const {
    os << name << " " << surname << " (" << age << " ani, Rol: " << getRole() << ", Bilet: " << ticket << ")";
}

    std::ostream& operator<<(std::ostream& os, const Person& p) {
        p.afisare(os);
        p.afisareBilete(os);
        return os;
    }
double Person::getTicketFinalPrice() const {
    if (ticket != nullptr) {
        return ticket->getFinalPrice(age);
    }
    return 0.0;
}

