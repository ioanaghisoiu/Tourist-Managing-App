#include <iostream>
#include <vector>
#include <string>
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
#include "Cerere.h"

void afiseazaMeniuUtilizator() {
    std::cout << "\n=== MENIU UTILIZATOR (PROFESOR) ===\n";
    std::cout << "1. Vizualizeaza Muzeu si Expozitii disponibile\n";
    std::cout << "2. Trimite cerere de programare vizita noua \n";
    std::cout << "3. Trimite cerere de anulare bilet pentru un student \n";
    std::cout << "4. Trimite cerere de anulare completa a grupului \n";
    std::cout << "0. Iesire din cont \n";
    std::cout << "Alege o optiune: ";
}

void afiseazaMeniuAdministrator() {
    std::cout << "\n=== MENIU ADMINISTRATOR ===\n";
    std::cout << "1. Vizualizeaza cererile trimise de profesori \n";
    std::cout << "2. Aproba si executa urmatoarea cerere din lista \n";
    std::cout << "3. Afiseaza toate grupurile aprobate din sistem \n";
    std::cout << "4. Administrare: Deblocheaza echipamentele interactive VR\n";
    std::cout << "0. Iesire din cont \n";
    std::cout << "Alege o optiune: ";
}

int main() {
    Location loc("Bucuresti", "Calea Victoriei 12", 179132);
    Museum antipa("Grigore Antipa", 101, loc);
    antipa.addExhibition(Exhibition("Lumea Insectelor", 15.0, 120));
    TemporaryExhibition fluturi("Fluturi Exotici", 10.0, 50, 5);
    InteractiveExhibition vr("Explorare Subacvatica VR", 30.0, 15, "Casti Oculus");

    std::vector<Group*> toateGrupurileAprobate;
    std::vector<Cerere> cereriInAsteptare;
    int urmatorulIdCerere = 1;

    Date dataViitoare(25, 12, 2026);
    Group* grupPrepopulat = new Group("Muzeul Grigore Antipa", 101, dataViitoare);
    Professor* profPrepopulat = new Professor("Dan", "Ionescu", 45, "dan.ionescu@scoala.ro", new Ticket(30.0, "RON", false), 15, "Liceul Tudor Vianu");
    grupPrepopulat->addMember(profPrepopulat);
    grupPrepopulat->addMember(new Student("Andrei", "Popescu", 16, "andrei@elev.ro", new DiscountTicket(30.0, "RON", 0.5), "Liceul Tudor Vianu", 10));
    toateGrupurileAprobate.push_back(grupPrepopulat);

    std::cout << "=== TOURIST MANAGING APP ACTIVATA ===\n";
    std::cout << "Data curenta a sistemului: " << Date::getToday() << "\n\n";

    std::string rolCurent = "";
    while (rolCurent != "iesire") {
        std::cout << "Sunteti administrator sau utilizator? (Scrieti exact rolul sau 'iesire'): ";
        std::getline(std::cin, rolCurent);

        if (rolCurent == "iesire") break;

        if (rolCurent == "administrator") {
            std::string parola;
            std::cout << "Introduceti parola de administrator: ";
            std::getline(std::cin, parola);

            if (parola != "Tourist-Managin-App-IOANA") {
                std::cout << "[ACCES RESPINS] Parola incorecta!\n\n";
                continue;
            }

            std::cout << "\n[ACCES CONFIRMAT] Autentificat ca Administrator.\n";
            int optAdmin = -1;
            while (optAdmin != 0) {
                afiseazaMeniuAdministrator();
                std::cin >> optAdmin;
                std::cin.ignore(10000, '\n');

                switch (optAdmin) {
                    case 1: {
                        std::cout << "\n--- CERERI IN ASTEPTARE DE LA UTILIZATORI ---\n";
                        if (cereriInAsteptare.empty()) {
                            std::cout << "Nu exista cereri noi in acest moment.\n";
                        } else {
                            for (const auto& c : cereriInAsteptare) {
                                std::cout << " ID Cerere: [" << c.getId() << "] | Tip: " << c.getTip() << "\n";
                                std::cout << " Descriere: " << c.getDescriere() << "\n-------------------------------------\n";
                            }
                        }
                        break;
                    }
                    case 2: {
                        std::cout << "\n--- PROCESARE SI APROBARE CERERE ---\n";
                        if (cereriInAsteptare.empty()) {
                            std::cout << "Nu exista nicio cerere de procesat.\n";
                            break;
                        }

                        Cerere c = cereriInAsteptare.front();
                        cereriInAsteptare.erase(cereriInAsteptare.begin());

                        if (c.getTip() == "PROGRAMARE") {
                            if (c.getDescriere().find("Ghid solicitat: DA") != std::string::npos) {
                                c.getGrupAsociat()->setGuide(new Guide("Elena", "Ghidul", 28, "elena@muzeu.ro", new Ticket(30.0, "RON", false), "Engleza", 999));
                                std::cout << "[ADMIN] Cererea ID " << c.getId() << " a fost aprobata cu GHID alocat!\n";
                            } else {
                                c.getGrupAsociat()->setGuide(nullptr);
                                std::cout << "[ADMIN] Cererea ID " << c.getId() << " a fost aprobata ca TUR LIBER (fara ghid)!\n";
                            }
                            toateGrupurileAprobate.push_back(c.getGrupAsociat());
                            (void)c.getGrupAsociat()->isReadyForVisit();
                        }
                        else if (c.getTip() == "ANULARE_STUDENT") {
                            try {
                                c.getGrupAsociat()->removeMember(c.getEmailTinta());
                                std::cout << "[ADMIN] Studentul cu email-ul " << c.getEmailTinta() << " a fost eliminat.\n";
                                std::cout << "\n[SISTEM NOTIFICARI EXTRA] Trimitere mesaj confirmare profesorului...\n";
                                std::cout << "Notificare: Solicitarea de anulare bilet pentru studentul (" << c.getEmailTinta()
                                          << ") a fost aprobata. Taxele grupului au fost recalculate dinamic!\n";
                            } catch (const std::exception& e) {
                                std::cout << "[EROARE LA EXECUTIE] " << e.what() << "\n";
                            }
                        }
                        else if (c.getTip() == "ANULARE_GRUP") {
                            auto it = toateGrupurileAprobate.begin();
                            while (it != toateGrupurileAprobate.end()) {
                                if (*it == c.getGrupAsociat()) {
                                    std::cout << "\n[SISTEM NOTIFICARI EXTRA] Trimitere mesaj confirmare profesorului...\n";
                                    std::cout << "Notificare: Solicitarea de anulare totala a vizitei din data de "
                                              << (*it)->getDataVizitei() << " a fost aprobata. Grupul a fost sters.\n";
                                    delete *it;
                                    toateGrupurileAprobate.erase(it);
                                    break;
                                }
                                ++it;
                            }
                            std::cout << "[ADMIN] Grupul a fost anulat si eliminat complet.\n";
                        }
                        break;
                    }
                    case 3: {
                        std::cout << "\n--- VIZUALIZARE PROGRAMARI DUPA DATA ---\n";
                        std::cout << "Introduceti data pentru cautare (Zi Luna An):\n";
                        Date dt; std::cin >> dt;
                        bool gasit = false;
                        for (Group* g : toateGrupurileAprobate) {
                            if (g->getDataVizitei() == dt) {
                                std::cout << "\n[GRUP PROGRAMAT IN DATA DE " << dt << "]:\n" << *g;
                                gasit = true;
                            }
                        }
                        if (!gasit) std::cout << "Nu exista grupuri aprobate pentru data de " << dt << ".\n";
                        break;
                    }
                    case 4:
                        vr.interact();
                        break;
                }
            }
        }
        else if (rolCurent == "utilizator") {
            std::cout << "\n[ACCES CONFIRMAT] Autentificat ca Utilizator (Profesor).\n";
            int optUtilizator = -1;
            while (optUtilizator != 0) {
                afiseazaMeniuUtilizator();
                std::cin >> optUtilizator;
                std::cin.ignore(10000, '\n');

                switch (optUtilizator) {
                    case 1:
                        std::cout << "\n" << antipa << "\n" << fluturi << "\n" << vr << "\n";
                        break;
                    case 2: {
                        std::cout << "\n--- SOLICITARE PROGRAMARE VIZITA NOUA ---\n";
                        std::cout << "Introduceti data dorita pentru vizita (Zi Luna An):\n";
                        Date dataDorita; std::cin >> dataDorita;
                        std::cin.ignore(10000, '\n');

                        std::string numeProf, prenumeProf, emailProf, scoalaProf;
                        int varstaProf, expProf;

                        std::cout << "\n--- Date Profesor (Coordonator) ---\n";
                        std::cout << "Nume: "; std::getline(std::cin, numeProf);
                        std::cout << "Prenume: "; std::getline(std::cin, prenumeProf);
                        std::cout << "Varsta: "; std::cin >> varstaProf;
                        std::cin.ignore(10000, '\n');
                        std::cout << "Email: "; std::getline(std::cin, emailProf);
                        std::cout << "Scoala/Liceul: "; std::getline(std::cin, scoalaProf);
                        std::cout << "Ani de experienta: "; std::cin >> expProf;
                        std::cin.ignore(10000, '\n');

                        std::string raspunsGhid;
                        std::cout << "\nDoriti tur cu ghid de la muzeu? (da/nu): ";
                        std::getline(std::cin, raspunsGhid);

                        Group* grupNou = new Group("Muzeul Grigore Antipa", 101, dataDorita);
                        grupNou->addMember(new Professor(numeProf, prenumeProf, varstaProf, emailProf, new Ticket(30.0, "RON", false), expProf, scoalaProf));

                        int nrStudenti = 0;
                        std::cout << "\nCati studenti doriti sa adaugati in grup? ";
                        std::cin >> nrStudenti;
                        std::cin.ignore(10000, '\n');

                        for (int i = 0; i < nrStudenti; ++i) {
                            std::string numeS, prenumeS, emailS;
                            int varstaS, anStudiu;

                            std::cout << "\n- Date Student " << (i + 1) << " -\n";
                            std::cout << "Nume: "; std::getline(std::cin, numeS);
                            std::cout << "Prenume: "; std::getline(std::cin, prenumeS);
                            std::cout << "Varsta: "; std::cin >> varstaS;
                            std::cin.ignore(10000, '\n');
                            std::cout << "Email: "; std::getline(std::cin, emailS);
                            std::cout << "An de studiu: "; std::cin >> anStudiu;
                            std::cin.ignore(10000, '\n');

                            try {
                                grupNou->addMember(new Student(numeS, prenumeS, varstaS, emailS, new DiscountTicket(30.0, "RON", 0.5), scoalaProf, anStudiu));
                            } catch (const std::exception& e) {
                                std::cout << "[EROARE LA ADAUGARE STUDENT] " << e.what() << "\n";
                            }
                        }

                        std::string descriereCerere = "Prof. " + numeProf + " " + prenumeProf + " solicita vizita pt " + std::to_string(nrStudenti) + " studenti. Ghid solicitat: ";
                        if (raspunsGhid == "da" || raspunsGhid == "DA" || raspunsGhid == "Da") {
                            descriereCerere += "DA";
                        } else {
                            descriereCerere += "NU";
                        }

                        Cerere nouaCerere(urmatorulIdCerere++, "PROGRAMARE", grupNou, "", descriereCerere);
                        cereriInAsteptare.push_back(nouaCerere);
                        std::cout << "\n[SUCCES] Solicitarea a fost trimisa administratorului spre aprobare!\n";
                        break;
                    }
                    case 3: {
                        std::cout << "\n--- SOLICITARE ANULARE BILET STUDENT ---\n";
                        Date azi = Date::getToday();

                        if (!(azi < grupPrepopulat->getDataVizitei())) {
                            std::cout << "[REFUZAT] Eroare politica anulare! Nu puteti trimite cereri de anulare in ziua vizitei sau dupa aceasta.\n";
                            break;
                        }

                        std::cout << "Introduceti email-ul studentului care nu mai poate veni: ";
                        std::string emailStergere; std::getline(std::cin, emailStergere);

                        Cerere nouaCerere(urmatorulIdCerere++, "ANULARE_STUDENT", grupPrepopulat, emailStergere, "Solicitare eliminare student cu email: " + emailStergere);
                        cereriInAsteptare.push_back(nouaCerere);
                        std::cout << "[SUCCES] Cererea de stergere a fost trimisa administratorului.\n";
                        break;
                    }
                    case 4: {
                        std::cout << "\n--- SOLICITARE ANULARE COMPLETA GRUP ---\n";
                        Date azi = Date::getToday();
                        if (!(azi < grupPrepopulat->getDataVizitei())) {
                            std::cout << "[REFUZAT] Nu puteti anula vizita in aceeasi zi!\n";
                            break;
                        }

                        Cerere nouaCerere(urmatorulIdCerere++, "ANULARE_GRUP", grupPrepopulat, "", "Solicitare anulare completa grup.");
                        cereriInAsteptare.push_back(nouaCerere);
                        std::cout << "[SUCCES] Solicitarea a fost trimisa catre administrator.\n";
                        break;
                    }
                }
            }
        }
        else {
            std::cout << "[OPTIUNE INVALIDA] Va rugam sa scrieti exact 'administrator' sau 'utilizator'.\n\n";
        }
    }

    for (Group* g : toateGrupurileAprobate) delete g;
    for (auto& c : cereriInAsteptare) {
        if (c.getTip() == "PROGRAMARE") delete c.getGrupAsociat();
    }

    std::cout << "\n--- Program Finalizat cu Succes ---\n";
    return 0;
}