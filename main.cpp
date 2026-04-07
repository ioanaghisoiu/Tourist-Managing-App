#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <algorithm>


class GroupThresholdException : public std::exception {
public:
    const char* what() const noexcept override {
        return "GroupThresholdException: Grupul nu poate avea mai mult de 10 membri.";
    }
};


class Date {
private:
    int d, m, y;
public:
    explicit Date(int d_ = 1, int m_ = 1, int y_ = 2024) : d{d_}, m{m_}, y{y_} {}
    bool isValid() const {
        if (y < 1800 || y > 2100) return false;
        if (m < 1 || m > 12) return false;
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))) daysInMonth[1] = 29;
        return d >= 1 && d <= daysInMonth[m - 1];
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& dt) {
        os << dt.d << "/" << dt.m << "/" << dt.y;
        return os;
    }

    bool operator==(const Date& other) const { return d == other.d && m == other.m && y == other.y; }
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

    bool operator==(const Ticket& other) const {
        return basePrice == other.basePrice && currency == other.currency &&
               isPriority == other.isPriority;
    }
    bool operator!=(const Ticket& other) const { return !(*this == other); }


    friend std::ostream& operator<<(std::ostream& os, const Ticket& t) {
        os << t.basePrice << " " << t.currency << (t.isPriority ? " (Priority)" : "");
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Date& dt) {
        std::cout << "Zi: "; is >> dt.d;
        std::cout << "Luna: "; is >> dt.m;
        std::cout << "An: "; is >> dt.y;
        return is;
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
    void setName(const std::string& newName) { name = newName; }
    void setSurname(const std::string& newSurname) { surname = newSurname; }
    int getAge() const { return age; }

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << p.name << " " << p.surname << " (" << p.age << " ani, Bilet: " << p.ticket << ")";
        return os;
    }

    void setEmail(const std::string& newEmail) {
        email = newEmail;
        validateEmail();
    }
    void setAge(int newAge) {
        if (newAge >= 0) age = newAge;
    }
    bool isMinor() const {
        return age < 18;
    }

    bool operator==(const Person& other) const {
        return name == other.name && surname == other.surname &&
               age == other.age && email == other.email;
    }
    bool operator!=(const Person& other) const { return !(*this == other); }
    bool operator<(const Person& other) const {
        return age < other.age;
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

    bool operator==(const Group& other) const {
        return museum_code == other.museum_code &&
               guide == other.guide && persons == other.persons;
    }
    bool operator!=(const Group& other) const { return !(*this == other); }
    bool operator<(const Group& other) const {
        return persons.size() < other.persons.size();
    }

    double calculateTotalRevenue() const {
        double total = 0;
        for (const auto& p : persons) {
            if (p.getAge() < 18) total += 10.0;
            else if (p.getAge() > 65) total += 15.0;
            else total += 25.0;
        }
        return total;
    }
};


class Location {
private:
    std::string county;
    std::string address;
    int sirutaCode;

public:

    Location(std::string county_, std::string address_, int siruta_)
        : county{std::move(county_)}, address{std::move(address_)}, sirutaCode{siruta_} {}

    Location() : county{"N/A"}, address{"N/A"}, sirutaCode{0} {}

    const std::string& getCounty() const { return county; }
    int getSirutaCode() const { return sirutaCode; }

    void updateAddress(const std::string& newAddress) {
        if (!newAddress.empty()) address = newAddress;
    }
    bool operator==(const Location& other) const {
        return county == other.county && address == other.address && sirutaCode == other.sirutaCode;
    }
    bool operator!=(const Location& other) const { return !(*this == other); }

    friend std::ostream& operator<<(std::ostream& os, const Location& loc) {
        os << loc.address << ", jud. " << loc.county << " (Cod SIRUTA: " << loc.sirutaCode << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Location& loc) {
        std::cout << "Judet: "; is >> loc.county;
        std::cout << "Adresa: "; is >> loc.address;
        std::cout << "Cod SIRUTA: "; is >> loc.sirutaCode;
        return is;
    }


};



class Exhibition {
private:
    std::string title;
    double extraFee;
    int itemsCount;

public:

    explicit Exhibition(std::string title_ = "Expozitie Generica", double fee_ = 0.0, int items_ = 0)
        : title{std::move(title_)},
          extraFee{fee_},
          itemsCount{items_}
    {}

    bool isPremiumExhibition() const {
        return extraFee > 50.0;
    }

    bool operator==(const Exhibition& other) const {
        return title == other.title && extraFee == other.extraFee && itemsCount == other.itemsCount;
    }

    bool operator<(const Exhibition& other) const {
        if (extraFee != other.extraFee)
            return extraFee < other.extraFee;
        return itemsCount < other.itemsCount;
    }

    int getEstimatedVisitTime() const {
        const int minutesPerItem = 2;
        return itemsCount * minutesPerItem;
    }

    double getExtraFee() const { return extraFee; }
    int getItemsCount() const { return itemsCount; }

    friend std::ostream& operator<<(std::ostream& os, const Exhibition& ex) {
        os << "  - " << ex.title << " (" << ex.itemsCount << " exponate) | Taxa: " << ex.extraFee << " RON";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Exhibition& ex) {
        std::cout << "Titlu expozitie: "; is >> ex.title;
        std::cout << "Taxa extra: "; is >> ex.extraFee;
        std::cout << "Numar exponate: "; is >> ex.itemsCount;
        return is;
    }

    void setTitle(const std::string& newTitle) {
        if (!newTitle.empty())
            title = newTitle;
    }
    void updatePrice(double newFee) {
        if (newFee >= 0)
            extraFee = newFee;
    }
    void addItems(int count) {
        if (count > 0)
            itemsCount += count;
    }

    std::string getTitle() const { return title; }
};



class Museum {
private:
    std::string name;
    long code;
    Location location;
    std::vector<Exhibition> exhibitions;
    static int totalMuseumsCreated;
    int* popularityVotes;
    int votesCapacity;

public:
    Museum(std::string name_, long code_, Location loc_, int cap_ = 5)
        : name{std::move(name_)}, code{code_}, location{std::move(loc_)}, votesCapacity{cap_} {
        popularityVotes = new int[votesCapacity]{0};
        totalMuseumsCreated++;
    }


    ~Museum() { delete[] popularityVotes; }

    Museum(const Museum& other)
        : name{other.name}, code{other.code}, location{other.location},
          exhibitions{other.exhibitions}, votesCapacity{other.votesCapacity} {
        popularityVotes = new int[votesCapacity];
        for (int i = 0; i < votesCapacity; ++i)
            popularityVotes[i] = other.popularityVotes[i];
    }

    Museum& operator=(const Museum& other) {
        if (this != &other) {
            name = other.name;
            code = other.code;
            location = other.location;
            exhibitions = other.exhibitions;

            int* newVotes = new int[other.votesCapacity];
            for (int i = 0; i < other.votesCapacity; ++i)
                newVotes[i] = other.popularityVotes[i];

            delete[] popularityVotes;
            popularityVotes = newVotes;
            votesCapacity = other.votesCapacity;
        }
        return *this;
    }

    static int getTotalMuseums() { return totalMuseumsCreated; }

    bool operator==(const Museum& other) const {
        if (code != other.code || name != other.name || !(location == other.location)) return false;
        if (exhibitions.size() != other.exhibitions.size()) return false;
        if (votesCapacity != other.votesCapacity) return false;
        for (int i = 0; i < votesCapacity; ++i) {
            if (popularityVotes[i] != other.popularityVotes[i]) return false;
        }
        return true;
    }


    int getTotalItemsCount() const {
        int total = 0;
        for (const auto& ex : exhibitions) {
            total += ex.getItemsCount();
        }
        return total;
    }

    void addExhibition(const Exhibition& ex) {
        exhibitions.push_back(ex);
    }

    bool hasExhibition(const std::string& searchTitle) const {
        for (const auto& ex : exhibitions) {
            if (ex.getTitle() == searchTitle) {
                return true;
            }
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Museum& m) {
        os << "MUZEU: " << m.name << " [Cod: " << m.code << "]\n"
           << "Locatie: " << m.location << "\n"
           << "Total exponate: " << m.getTotalItemsCount() << "\n"
           << "Expozitii active:\n";
        for (const auto& e : m.exhibitions) os << e << "\n";
        return os;
    }
};
int Museum::totalMuseumsCreated = 0;

class MuseumApp {
public:
    static void run() {
        std::cout << "Tourist Managing App\n";

        Location loc("Bucuresti", "Calea Victoriei 12", 179132);
        Museum antipa("Grigore Antipa", 101, loc);
        antipa.addExhibition(Exhibition("Lumea Insectelor", 15.0, 120));
        antipa.addExhibition(Exhibition("Comorile Adancurilor", 25.0, 45));

        std::cout << antipa << std::endl;

        Person guide("Ion", "Popescu", 35, "ion.p@museum.ro", 0);
        Person p1("Andrei", "Ionescu", 20, "andrei@mail.com", 30.0);
        Person p2("Maria", "Enache", 15, "maria@mail.com", 30.0);

        std::vector<Person> initialMembers = {p1};
        Group group(initialMembers, guide, 101);

        try {
            group.addMember(p2);
            std::cout << "Membru adaugat cu succes.\n";
            group.addMember(p1);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        std::cout << "Statistici Grup:\n";
        std::cout << "Varsta medie: " << group.calculateAverageAge() << " ani\n";
        std::cout << "Venit total estimat: " << group.calculateTotalRevenue() << " RON\n";
        std::cout << "Grupul este pregatit: " << (group.isReadyForVisit() ? "DA" : "NU") << "\n";

        std::cout << "--- Detalii Grup Complete ---\n" << group << std::endl;


        Person p3 = p1;
        std::cout << (p1 == p3 ? "Persoane egale\n" : "Persoane diferite\n");
        std::cout << (p1 == p2 ? "Persoane egale\n" : "Persoane diferite\n");


        std::vector<Person> sortedPersons = {p2, p1, guide};
        std::sort(sortedPersons.begin(), sortedPersons.end());
        std::cout << "Persoane sortate dupa varsta:\n";
        for (const auto& p : sortedPersons) std::cout << " - " << p << "\n";

        Date d1(15, 3, 2024);
        std::cout << "Data: " << d1 << " este valida: " << (d1.isValid() ? "DA" : "NU") << "\n";
        Date d2(31, 2, 2024);
        std::cout << "Data: " << d2 << " este valida: " << (d2.isValid() ? "DA" : "NU") << "\n";


        Ticket t1(30.0, "RON", false);
        Ticket t2(50.0, "RON", true);
        std::cout << "Pret final pentru copil (15 ani): " << t1.getFinalPrice(15) << " RON\n";
        std::cout << "Pret final pentru adult (30 ani): " << t1.getFinalPrice(30) << " RON\n";
        std::cout << "Pret final pentru senior (70 ani): " << t1.getFinalPrice(70) << " RON\n";
        std::cout << "Pret bilet priority pentru adult: " << t2.getFinalPrice(30) << " RON\n";


        Exhibition ex1("Arta Moderna", 60.0, 30);
        std::cout << "\nExpozitie premium: " << (ex1.isPremiumExhibition() ? "DA" : "NU") << "\n";
        std::cout << "Timp estimat vizita: " << ex1.getEstimatedVisitTime() << " minute\n";
        ex1.addItems(10);
        std::cout << "Dupa addItems(10): " << ex1 << "\n";
        ex1.updatePrice(45.0);
        std::cout << "Dupa updatePrice(45): " << ex1 << "\n";
        ex1.setTitle("Arta Contemporana");
        std::cout << "Dupa setTitle: " << ex1 << "\n";


        std::cout << "\nMuzeul are expozitia 'Lumea Insectelor': "
                  << (antipa.hasExhibition("Lumea Insectelor") ? "DA" : "NU") << "\n";
        std::cout << "Muzeul are expozitia 'Arta Moderna': "
                  << (antipa.hasExhibition("Arta Moderna") ? "DA" : "NU") << "\n";
        std::cout << "Total exponate in muzeu: " << antipa.getTotalItemsCount() << "\n";


        loc.updateAddress("Calea Victoriei 99");
        std::cout << "Adresa actualizata: " << loc << "\n";


        std::cout << "Test limita grup (max 10 membri):\n";
        Group groupFull(initialMembers, guide, 101);
        try {
            for(int i = 0; i < 10; i++) {
                groupFull.addMember(Person("Test" + std::to_string(i), "User", 25,
                                   "test" + std::to_string(i) + "@mail.com", 20.0));
            }
        } catch (const GroupThresholdException& e) {
            std::cerr << e.what() << "\n";
        }

        Museum antipaCopy = antipa;
        std::cout << "Copie muzeu creata. Total muzee: " << Museum::getTotalMuseums() << "\n";

        std::cout << "\n--- Adauga expozitie noua ---\n";
        Exhibition exNou;
        std::cin >> exNou;
        std::cout << "Expozitie introdusa: " << exNou << "\n";
        antipa.addExhibition(exNou);
        std::cout << "Total exponate acum: " << antipa.getTotalItemsCount() << "\n";

        std::cout << "\n--- Adauga locatie noua ---\n";
        Location locNou;
        std::cin >> locNou;
        std::cout << "Locatie introdusa: " << locNou << "\n";

        std::cout << "\n--- Verifica data vizitei ---\n";
        Date dNou;
        std::cin >> dNou;
        std::cout << "Data introdusa: " << dNou << " - valida: " << (dNou.isValid() ? "DA" : "NU") << "\n";

        std::cout << "\n--- Program Finalizat ---" << std::endl;
    }
};


int main()
{
    MuseumApp::run();
    return 0;
}