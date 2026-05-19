#include <iostream>
#include <vector>
#include "Location.h"
#include "Museum.h"
#include "Group.h"
#include "Student.h"
#include "Professor.h"
#include "Guide.h"
#include "Exceptions.h"
#include "Ticket.h"
#include "VipTicket.h"
#include "DiscountTicket.h"
#include "TemporaryExhibition.h"
#include "InteractiveExhibition.h"
#include "Date.h"

void afiseazaMeniu() {
    std::cout << "\n=== Tourist Managing App - Meniu Principal ===\n";
    std::cout << "1. Afiseaza detalii Muzeu si Expozitii\n";
    std::cout << "2. Adauga un Student in grupul curent\n";
    std::cout << "3. Adauga un Profesor in grupul curent\n";
    std::cout << "4. Seteaza Ghid si porneste vizita (Calculeaza Taxe)\n";
    std::cout << "5. Interactioneaza cu Expozitia VR\n";
    std::cout << "6. Cauta si afiseaza programarile dintr-o anumita data\n";
    std::cout << "0. Iesire din aplicatie\n";
    std::cout << "Alege o optiune: ";
}

int main() {

    Location loc("Bucuresti", "Calea Victoriei 12", 179132);
    Museum antipa("Grigore Antipa", 101, loc);


    antipa.addExhibition(Exhibition("Lumea Insectelor", 15.0, 120));
    TemporaryExhibition fluturi("Fluturi Exotici", 10.0, 50, 5);
    InteractiveExhibition vr("Explorare Subacvatica VR", 30.0, 15, "Casti Oculus");

    std::vector<Group*> toateGrupurile;

    Date data1(15, 5, 2026);
    Group* g1 = new Group("Muzeul Grigore Antipa", 101, data1);
    g1->addMember(new Student("Andrei", "Popescu", 16, "andrei@elev.ro", new Ticket(30.0, "RON", false), "Liceul Tudor Vianu", 10));
    toateGrupurile.push_back(g1);

    Date data2(20, 5, 2026);
    Group* g2 = new Group("Muzeul Grigore Antipa", 101, data2);
    g2->addMember(new Professor("Dan", "Ionescu", 45, "dan.ionescu@scoala.ro", new Ticket(30.0, "RON", false), 15, "Liceul Tudor Vianu"));
    toateGrupurile.push_back(g2);

    Group* grupCurent= g1;

    int optiune = -1;

    while (optiune != 0) {
        afiseazaMeniu();
        std::cin >> optiune;


        std::cin.ignore(10000, '\n');

        switch (optiune) {
            case 1: {
                std::cout << "\n--- DETALII MUZEU ---\n";
                std::cout << antipa << "\n";
                std::cout << fluturi << "\n";
                std::cout << vr << "\n";
                break;
            }
            case 2: {
                std::cout << "\n--- ADAUGARE STUDENT ---\n";
                std::string nume, email;
                int varsta;
                std::cout << "Nume student: "; std::getline(std::cin, nume);
                std::cout << "Email: "; std::getline(std::cin, email);
                std::cout << "Varsta: "; std::cin >> varsta;


                try {
                    Ticket* biletRedus = new DiscountTicket(30.0, "RON", 0.5);
                    grupCurent->addMember(new Student(nume, "Studentescu", varsta, email, biletRedus, "Liceu", 10));
                    std::cout << "[SUCCES] Student adaugat in grup!\n";
                } catch (const DuplicateEmailException& e) {
                    std::cout << "[EROARE PRINSA] " << e.what() << "\n";
                } catch (const GroupThresholdException& e) {
                    std::cout << "[EROARE PRINSA] " << e.what() << "\n";
                }
                break;
            }
            case 3: {
                std::cout << "\n--- ADAUGARE PROFESOR (VIP) ---\n";
                try {

                    Ticket* biletVip = new VipTicket(30.0, "RON", 100.0);
                    grupCurent->addMember(new Professor("Dan", "Ionescu", 45, "dan.ionescu@scoala.ro", biletVip, 15, "Liceul Vianu"));
                    std::cout << "[SUCCES] Profesor adaugat in grup!\n";
                } catch (const std::exception& e) {
                    std::cout << "[EROARE] " << e.what() << "\n";
                }
                break;
            }
            case 4: {
                std::cout << "\n--- SETARE GHID SI INCEPERE VIZITA ---\n";
                grupCurent->setGuide(new Guide("Elena", "Ghidul", 28, "elena@muzeu.ro", new Ticket(30.0, "RON", false), "Engleza", 999));

                if (grupCurent->isReadyForVisit()) {
                    std::cout << "\n Vizita poate incepe! Total de plata pe grup: "
                              << grupCurent->calculateTotalRevenue() << " RON\n";
                    std::cout << "\n--- Componenta Grup ---\n" << grupCurent << "\n";
                } else {
                    std::cout << "Grupul nu este gata (Adaugati membri mai intai).\n";
                }
                break;
            }
            case 5: {
                std::cout << "\n--- INTERACTIUNE EXPOZITIE ---\n";

                vr.interact();
                break;
            }
            case 6: {
                std::cout << "\n--- FILTRARE / CAUTARE PROGRAMARI DUPA DATA ---\n";
                std::cout << "Introduceti data pe care o cautati:\n";
                Date dataCautata;
                std::cin >> dataCautata;

                bool gasit = false;

                for (Group* g : toateGrupurile) {
                    if (g->getDataVizitei() == dataCautata) {
                        std::cout << "\n[GRUP PROGRAMAT IN DATA DE " << dataCautata << "]:\n";
                        std::cout << *g << "-------------------------------------------\n";
                        gasit = true;
                    }
                }
                if (!gasit) {
                    std::cout << "\nNu exista grupuri programate in data de " << dataCautata << ".\n";
                }
                break;
            }
            case 0: {
                std::cout << "\nSe inchide aplicatia. La revedere!\n";
                break;
            }
            default: {
                std::cout << "\nOptiune invalida! Incercati din nou.\n";
                break;
            }
        }
    }

    return 0;
}