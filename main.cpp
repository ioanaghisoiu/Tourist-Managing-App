#include <iostream>
#include <array>
#include <vector>

#include "include/Example.h"
// This also works if you do not want `include/`, but some editors might not like it
// #include "Example.h"

class Person {
private:
    std::string name;
    std::string surname;
    int age;
    std::string email;
public:
    Person(const std::string& name_, const std::string& surname_, int age_, const std::string& email_):
    name(name_), surname(surname_), age(age_), email(email_) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& p)
    {
        os<<"Name: "<<p.name<<" ,Surname: "<< p.surname<< ", Age: "<<p.age<<", Email: "<<p.email<<"\n";
        return os;
    }
};


class Group {
private:
    std::vector<Person> persons;
    Person guide;
    long museum_code;
public:
    Group(const std::vector<Person>& persons_, const Person& guide_, long museum_code_) :
        persons(persons_), guide(guide_), museum_code(museum_code_) {}

    friend std::ostream& operator<<(std::ostream& os, const Group& g) {
        os << "Group for Museum Code: " << g.museum_code << ", Guide: " << g.guide;
        os << ", Members: ";
        for (const auto& group : g.persons) {
            os << " - " << group;
        }
        return os;
    }
};

class Location {
private:
    std:: string country;
    std:: string address;
public:
    Location(const std::string& country_, const std::string& address_): country(country_), address(address_) {}

    friend std::ostream& operator<<(std::ostream& os, const Location& l) {
       os<<"Country: "<<l.country<<", Adress: "<<l.address<<"\n";
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

    Museum (const Museum& other) : name(other.name), code(other.code), location(other.location) {}

    Museum& operator=(const Museum& other) {
        name = other.name;
        code = other.code;
        location = other.location;
        return *this;
    }

    ~Museum(){}

    friend std::ostream& operator<<(std::ostream& os, const Museum& m) {
        os<<"Museum name: "<<m.name<<", Code"<<m.code<<", Location: "<<m.location<<"\n";
        return os;
    }
};




int main() {
    std::cout << "Hello, world!\n";
    Example e1;
    e1.g();
    std::array<int, 100> v{};
    int nr;
    std::cout << "Introduceți nr: ";
    /////////////////////////////////////////////////////////////////////////
    /// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
    /// dați exemple de date de intrare folosind fișierul tastatura.txt
    /// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
    /// (în formatul impus de voi) astfel încât execuția programului să se încheie.
    /// De asemenea, trebuie să adăugați în acest fișier date de intrare
    /// pentru cât mai multe ramuri de execuție.
    /// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
    /// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
    ///
    /// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
    /// pentru a simula date introduse de la tastatură.
    /// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
    ///
    /// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
    /// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
    /// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
    /// program care merg (și să le evitați pe cele care nu merg).
    ///
    /////////////////////////////////////////////////////////////////////////
    std::cin >> nr;
    /////////////////////////////////////////////////////////////////////////
    for(int i = 0; i < nr; ++i) {
        std::cout << "v[" << i << "] = ";
        std::cin >> v[i];
    }
    std::cout << "\n\n";
    std::cout << "Am citit de la tastatură " << nr << " elemente:\n";
    for(int i = 0; i < nr; ++i) {
        std::cout << "- " << v[i] << "\n";
    }
    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
    ///
    ///////////////////////////////////////////////////////////////////////////
    return 0;
}