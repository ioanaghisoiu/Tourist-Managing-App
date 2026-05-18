#include <iostream>
#include "Location.h"
#include "Museum.h"
#include "Exhibition.h"
#include "Date.h"
#include "Group.h"
#include "Student.h"
#include "Professor.h"
#include "Guide.h"
#include "Exceptions.h"
#include "Ticket.h"
#include "VipTicket.h"
#include "DiscountTicket.h"

int main() {
    std::cout << "--- Tourist Managing App ---\n\n";

    Location loc("Bucuresti", "Calea Victoriei 12", 179132);
    Museum antipa("Grigore Antipa", 101, loc);
    antipa.addExhibition(Exhibition("Lumea Insectelor", 15.0, 120));
    antipa.addExhibition(Exhibition("Comorile Adancurilor", 25.0, 45));

    std::cout << antipa << "\n";

    Group grup("Muzeul Grigore Antipa", 101);

    try {
        grup.addMember(new Professor("Dan", "Ionescu", 45, "dan.ionescu@scoala.ro", new Ticket(30.0, "RON", false), 15, "Liceul Tudor Vianu"));
        std::cout << "Profesor adaugat.\n";

        grup.addMember(new Student("Andrei", "Popescu", 16, "andrei@elev.ro", new Ticket(30.0, "RON", false), "Liceul Tudor Vianu", 10));
        std::cout << "Student 1 adaugat.\n";

        grup.addMember(new Student("Mihai", "Radu", 17, "andrei@elev.ro", new Ticket(30.0, "RON", false), "Liceul Tudor Vianu", 11));

    } catch (const DuplicateEmailException& e) {
        std::cout << " [PRINS EROARE] " << e.what() << "\n";
    }

    try {
        double bani = grup.calculateTotalRevenue();
        std::cout << "Bani incasati: " << bani << " RON\n";
    } catch (const InvalidGroupStateException& e) {
        std::cout << " [PRINS EROARE] " << e.what() << "\n";
    }


    grup.setGuide(new Guide("Elena", "Ghidul", 28, "elena@muzeu.ro", new Ticket(30.0, "RON", false), "Engleza", 999));
    std::cout << "Ghid setat.\n";

    if (grup.isReadyForVisit()) {
        std::cout << "\n--- NOTIFICARI SISTEM ---\n";

        std::cout << "\nTotal de incasat : " << grup.calculateTotalRevenue() << " RON\n";
        std::cout << "\nDetalii complete grup :\n" << grup << "\n";
    }

    Ticket* biletVip = new VipTicket(50.0, "RON", 150.0);
    Ticket* biletRedus = new DiscountTicket(50.0, "RON", 0.3);
    Ticket* biletNormal = new Ticket(50.0, "RON", false);

    Student s1("Ion", "Popescu", 20, "ion@email.com", biletRedus, "UPB", 9);
    Professor p1("Maria", "Ionescu", 45, "maria@email.com", biletVip, 10, "Mate");
    Guide g1("Alex", "Vasile", 30, "alex@email.com", biletNormal, "Engleza", 5);


    std::cout << s1 << "\n";
    std::cout << p1 << "\n";
    std::cout << g1 << "\n";

    std::cout << "\n--- Program Finalizat cu Succes ---\n";
    return 0;
}