#include <iostream>
#include <string>
#include <vector>
#include <exception>


class GroupThresholdException : public std::exception {
public:
    const char* what() const noexcept override {
        return "GroupThresholdException: Grupul nu poate avea mai mult de 10 membri.";
    }
};


class Ticket {
private:
    double basePrice;
    std::string currency;
    bool isPriority;

public:
    Ticket(double price = 0, std::string curr = "RON", bool priority = false)
        : basePrice(price), currency(curr), isPriority(priority) {}

    double getFinalPrice(int age) const {
        double discount = 0;
        if (age < 18) discount = 0.5;
        else if (age > 65) discount = 0.3;
        double price = basePrice * (1.0 - discount);
        if (isPriority) price += 10.0;
        return price;
    }

    friend std::ostream& operator<<(std::ostream& os, const Ticket& t) {
        os << t.basePrice << " " << t.currency << (t.isPriority ? " (Priority)" : "");
        return os;
    }
};


class Person {
private:
    std::string name;
    std::string surname;
    int age;
    std::string email;
    Ticket ticket;

public:
    Person(const std::string& name_, const std::string& surname_, int age_, const std::string& email_, double tPrice) :
        name(name_), surname(surname_), age(age_), email(email_), ticket(tPrice) {}

    void validateEmail() const {
        size_t atPos = email.find('@');
        size_t dotPos = email.find('.');
        if (atPos == std::string::npos || dotPos == std::string::npos || atPos == 0 || atPos == email.length() - 1) {
            std::cout << "Avertisment: Format email invalid pentru " << name << "\n";
            return;
        }
        std::cout << "Email validat pentru " << name << ".\n";
    }

    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    int getAge() const { return age; }

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << p.name << " " << p.surname << " (" << p.age << " ani, Bilet: " << p.ticket << ")";
        return os;
    }
};


class Group {
private:
    std::vector<Person> persons;
    Person guide;
    long museum_code;

    bool isEmailDuplicate(const std::string& email) const {
        for (const auto& p : persons) {
            if (p.getEmail() == email) return true;
        }
        return false;
    }

public:
    Group(const std::vector<Person>& persons_, const Person& guide_, long museum_code_) :
        persons(persons_), guide(guide_), museum_code(museum_code_) {
        guide.validateEmail();
    }

    friend std::ostream& operator<<(std::ostream& os, const Group& g) {
        os << "Grup Muzeu [" << g.museum_code << "]\nGhid: " << g.guide << "\nMembri:\n";
        for (const auto& p : g.persons) os << " - " << p << "\n";
        return os;
    }

    void addMember(const Person& member) {
        if (persons.size() >= 10) throw GroupThresholdException();
        if (isEmailDuplicate(member.getEmail())) {
            std::cout << "Eroare: Email duplicat: " << member.getEmail() << "\n";
            return;
        }
        persons.push_back(member);
    }

    double calculateAverageAge() const {
        if (persons.empty()) return 0.0;
        double sum = 0;
        for (const auto& p : persons) sum += p.getAge();
        return sum / (double)persons.size();
    }

    bool isReadyForVisit() const {
        return !persons.empty() && persons.size() <= 10 && guide.getAge() >= 18 && museum_code != 0;
    }
};


class Location {
private:
    std::string country;
    std::string address;
public:
    Location(const std::string& country_, const std::string& address_) : country(country_), address(address_) {}
    friend std::ostream& operator<<(std::ostream& os, const Location& l) {
        os << l.address << ", " << l.country;
        return os;
    }
};


class Museum {
private:
    std::string name;
    long code;
    Location location;
public:
    Museum(const std::string& name_, long code_, const Location& location_) : name(name_), code(code_), location(location_) {}
    Museum(const Museum& other) : name(other.name), code(other.code), location(other.location) {}
    Museum& operator=(const Museum& other) {
        if (this != &other) { name = other.name; code = other.code; location = other.location; }
        return *this;
    }
    ~Museum() {}
    friend std::ostream& operator<<(std::ostream& os, const Museum& m) {
        os << "Muzeu: " << m.name << " (Cod: " << m.code << ") | Locatie: " << m.location;
        return os;
    }
};


int main() {
    try {
        Location loc("Romania", "Calea Victoriei 12");
        Museum m1("Muzeul de Arta", 505, loc);


        Museum m2 = m1;

        Person ghid("Ion", "Ghidul", 35, "ion4@gmail.com", 0);
        std::vector<Person> init;
        Group grup1(init, ghid, 505);


        int nr;
        std::cout << "Cati vizitatori adaugam? ";
        if(!(std::cin >> nr)) nr = 0;

        for(int i = 0; i < nr; ++i) {
            std::string n, s, e;
            int a;
            double p;
            std::cout << "Date (Nume Prenume Varsta Email PretBilet): ";
            std::cin >> n >> s >> a >> e >> p;
            Person v(n, s, a, e, p);
            v.validateEmail();
            grup1.addMember(v);
        }

        std::cout << "\n---VIZITA---\n";
        std::cout << m1 << "\n" << grup1 << "\n";
        std::cout << "Medie varsta: " << grup1.calculateAverageAge() << "\n";

        if(grup1.isReadyForVisit()) std::cout << "Grupul poate intra!\n";

    } catch (const std::exception& ex) {
        std::cerr << "Eroare: " << ex.what() << "\n";
    }
    return 0;
}