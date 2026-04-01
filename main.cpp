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

class Person {
private:
    std::string name;
    std::string surname;
    int age;
    std::string email;

public:
    Person(const std::string& name_, const std::string& surname_, int age_, const std::string& email_) :
        name(name_), surname(surname_), age(age_), email(email_) {}


    void validateEmail() const {
        size_t atPos = email.find('@');
        size_t dotPos = email.find('.');

        if (atPos == std::string::npos || dotPos == std::string::npos ||
            atPos == 0 || atPos == email.length() - 1) {
            std::cout << "Avertisment: Format email invalid pentru " << name << "\n";
            return;
        }
        std::cout << "Email validat pentru " << name << ".\n";
    }


    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    int getAge() const { return age; }


    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << p.name << " " << p.surname << " (Varsta: " << p.age << ", Email: " << p.email << ")";
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
        os << "Grup Muzeu [" << g.museum_code << "]\n";
        os << "Ghid: " << g.guide << "\n";
        os << "Membri (" << g.persons.size() << "):\n";
        for (const auto& p : g.persons) {
            os << " - " << p << "\n";
        }
        return os;
    }

    void addMember(const Person& member) {
        if (persons.size() >= 10) throw GroupThresholdException();

        if (isEmailDuplicate(member.getEmail())) {
            std::cout << "Eroare: Email duplicat in grup!\n";
            return;
        }
        persons.push_back(member);
    }


    double calculateAverageAge() const {
        if (persons.empty())
            return 0.0;
        double sum = 0;
        for (const auto& p : persons)
            sum += p.getAge();
        return sum / persons.size();
    }


    bool isReadyForVisit() const {
        bool sizeOk = !persons.empty() && persons.size() <= 10;
        bool guideOk = guide.getAge() >= 18;
        bool experienceOk = guide.getAge() > calculateAverageAge();

        return sizeOk && guideOk && experienceOk && museum_code != 0;
    }
};

class Location {
private:
    std::string country;
    std::string address;

public:
    Location(const std::string& country_, const std::string& address_) :
        country(country_), address(address_) {}

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
    Museum(const std::string& name_, long code_, const Location& location_) :
        name(name_), code(code_), location(location_) {}


    Museum(const Museum& other) : name(other.name), code(other.code), location(other.location) {}

    Museum& operator=(const Museum& other) {
        if (this != &other) {
            name = other.name;
            code = other.code;
            location = other.location;
        }
        return *this;
    }

    ~Museum() {}

    friend std::ostream& operator<<(std::ostream& os, const Museum& m) {
        os << "Muzeu: " << m.name << " (Cod: " << m.code << ") | Locatie: " << m.location;
        return os;
    }
};

int main() {

    return 0;
}