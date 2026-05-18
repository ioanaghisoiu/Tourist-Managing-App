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

int main() {
    std::cout << "--- Tourist Managing App ---\n\n";

    Location loc("Bucuresti", "Calea Victoriei 12", 179132);
    Museum antipa("Grigore Antipa", 101, loc);
    antipa.addExhibition(Exhibition("Lumea Insectelor", 15.0, 120));
    antipa.addExhibition(Exhibition("Comorile Adancurilor", 25.0, 45));

    std::cout << antipa << "\n";

    Group grup("Muzeul Grigore Antipa", 101);

    try {
        grup.addMember(new Professor("Dan", "Ionescu", 45, "dan.ionescu@scoala.ro", 30.0, 15, "Liceul Tudor Vianu"));
        std::cout << "Profesor adaugat.\n";

        grup.addMember(new Student("Andrei", "Popescu", 16, "andrei@elev.ro", 30.0, "Liceul Tudor Vianu", 10));
        std::cout << "Student 1 adaugat.\n";

        grup.addMember(new Student("Mihai", "Radu", 17, "andrei@elev.ro", 30.0, "Liceul Tudor Vianu", 11));

    } catch (const DuplicateEmailException& e) {
        std::cout << " [PRINS EROARE] " << e.what() << "\n";
    }


    try {
        double bani = grup.calculateTotalRevenue();
        std::cout << "Bani incasati: " << bani << " RON\n";
    } catch (const InvalidGroupStateException& e) {
        std::cout << " [PRINS EROARE] " << e.what() << "\n";
    }

    std::cout << "\n3. Reparare grup si finalizare vizita:\n";
    grup.setGuide(new Guide("Elena", "Ghidul", 28, "elena@muzeu.ro", 30.0, "Engleza", 999));
    std::cout << " [OK] Ghid setat.\n";

    if (grup.isReadyForVisit()) {
        std::cout << "\n--- NOTIFICARI SISTEM ---\n";

        std::cout << "\nTotal de incasat (polimorfic): " << grup.calculateTotalRevenue() << " RON\n";
        std::cout << "\nDetalii complete grup (NVI - operator<< polimorfic):\n" << grup << "\n";
    }

    std::cout << "\n--- Program Finalizat cu Succes ---\n";
    return 0;
}