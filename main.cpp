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

class MesajNotificare {
public:
    std::string emailProfesor;
    std::string textMesaj;
};

void afiseazaMeniuUtilizator() {
    std::cout << "\n=== MENIU UTILIZATOR (PROFESOR) ===\n";
    std::cout << "1. Vizualizeaza Muzeu si Expozitii disponibile\n";
    std::cout << "2. Trimite cerere de programare vizita noua \n";
    std::cout << "3. Trimite cerere de anulare bilet pentru un student \n";
    std::cout << "4. Trimite cerere de anulare completa a grupului \n";
    std::cout << "5. Vizualizeaza status programare si notificari primite\n";
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
    std::vector<Professor*> conturiProfesori;
    std::vector<MesajNotificare> cutiePostalaNotificari;
    int urmatorulIdCerere = 1;


    Date dataViitoare(25, 12, 2026);
    Group* grupPrepopulat = new Group("Muzeul Grigore Antipa", 101, dataViitoare);
    Professor* profPrepopulat = new Professor("Dan", "Ionescu", 45, "dan.ionescu@scoala.ro", new Ticket(30.0, "RON", false), 15, "Liceul Tudor Vianu");

    grupPrepopulat->addMember(profPrepopulat->clone());
    grupPrepopulat->addMember(new Student("Andrei", "Popescu", 16, "andrei@elev.ro", new DiscountTicket(30.0, "RON", 0.5), "Liceul Tudor Vianu", 10));

    toateGrupurileAprobate.push_back(grupPrepopulat);
    conturiProfesori.push_back(profPrepopulat);

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

            if (parola != "Ghisoiu.Ioana") {
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

                        std::string emailProfAsociat = "";
                        if (c.getGrupAsociat() && c.getDescriere().find("[REF:") != std::string::npos) {
                            emailProfAsociat = c.getDescriere().substr(c.getDescriere().find("[REF:") + 5);
                            emailProfAsociat = emailProfAsociat.substr(0, emailProfAsociat.find("]"));
                        }

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

                            MesajNotificare notif;
                            notif.emailProfesor = emailProfAsociat;
                            notif.textMesaj = "Cererea dumneavoastra de programare a fost aprobata de Administrator!";
                            cutiePostalaNotificari.push_back(notif);
                        }
                        else if (c.getTip() == "ANULARE_STUDENT") {
                            try {
                                c.getGrupAsociat()->removeMember(c.getEmailTinta());
                                std::cout << "[ADMIN] Studentul cu email-ul " << c.getEmailTinta() << " a fost eliminat.\n";


                                double totalNou = c.getGrupAsociat()->calculateTotalRevenue();

                                MesajNotificare notif;
                                notif.emailProfesor = emailProfAsociat;
                                notif.textMesaj = "Studentul (" + c.getEmailTinta() + ") a fost sters. Noul total de plata al grupului este: " + std::to_string(totalNou) + " RON.";
                                cutiePostalaNotificari.push_back(notif);
                            } catch (const std::exception& e) {
                                std::cout << "[EROARE LA EXECUTIE] " << e.what() << "\n";
                            }
                        }
                        else if (c.getTip() == "ANULARE_GRUP") {
                            auto it = toateGrupurileAprobate.begin();
                            while (it != toateGrupurileAprobate.end()) {
                                if (*it == c.getGrupAsociat()) {
                                    MesajNotificare notif;
                                    notif.emailProfesor = emailProfAsociat;
                                    notif.textMesaj = "Notificare: Solicitarea de anulare completa a grupului dumneavoastra a fost aprobata. Programarea a fost stearsa.";
                                    cutiePostalaNotificari.push_back(notif);

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
            std::string logNume, logPrenume, logParola;
            std::cout << "Numele : "; std::getline(std::cin, logNume);
            std::cout << "Prenume : "; std::getline(std::cin, logPrenume);
            std::cout << "Parola (Nume.Prenume): "; std::getline(std::cin, logParola);

            std::string parolaAsteptata = logNume + "."+ logPrenume;
            if (logParola != parolaAsteptata) {
                std::cout << "[ACCES RESPINS] Parola incorecta!\n\n";
                continue;
            }

            std::string emailUtilizatorCurent = logNume + "." + logPrenume + "@scoala.ro";
            Professor* profesorLogat = nullptr;

            for (Professor* p : conturiProfesori) {
                if (p->getEmail() == emailUtilizatorCurent) { profesorLogat = p; break; }
            }

            if (profesorLogat == nullptr) {
                std::cout << "\n--- CREARE CONT NOU PROFESOR ---\n";
                int varstaP, expP;
                std::string scoalaP;
                std::cout << "Varsta dumneavoastra: "; std::cin >> varstaP; std::cin.ignore(10000, '\n');
                std::cout << "Ani de experienta: "; std::cin >> expP; std::cin.ignore(10000, '\n');
                std::cout << "Scoala/Liceul la care predati: "; std::getline(std::cin, scoalaP);

                profesorLogat = new Professor(logNume, logPrenume, varstaP, emailUtilizatorCurent, new Ticket(30.0, "RON", false), expP, scoalaP);
                conturiProfesori.push_back(profesorLogat);
                std::cout << "[CONT CREAT CU SUCCES]\n";
            }
            std::cout << "\n[ACCES CONFIRMAT] Bun venit, " << profesorLogat->getName() << ".\n";

            int optUtilizator = -1;
            while (optUtilizator != 0) {
                afiseazaMeniuUtilizator();
                std::cin >> optUtilizator;

                Group* grupAsociatUtilizator = nullptr;
                for (Group* g : toateGrupurileAprobate) {
                    if (g->areMembru(profesorLogat->getEmail())) { grupAsociatUtilizator = g; break; }
                }
                std::cin.ignore(10000, '\n');

                switch (optUtilizator) {
                    case 1:
                        std::cout << "\n" << antipa << "\n" << fluturi << "\n" << vr << "\n";
                        break;
                    case 2: {
                        std::cout << "\n--- SOLICITARE PROGRAMARE VIZITA NOUA ---\n";
                        if (grupAsociatUtilizator != nullptr) {
                            std::cout << "[LIMITARE] Aveti deja o vizita activa aprobata in sistem! Nu puteti programa alta.\n";
                            break;
                        }

                        std::cout << "Introduceti data dorita pentru vizita (Zi Luna An):\n";
                        Date dataDorita; std::cin >> dataDorita;
                        std::cin.ignore(10000, '\n');

                        std::string raspunsGhid;
                        std::cout << "\nDoriti tur cu ghid de la muzeu? (da/nu): ";
                        std::getline(std::cin, raspunsGhid);

                        Group* grupNou = new Group("Muzeul Grigore Antipa", 101, dataDorita);
                        grupNou->addMember(profesorLogat->clone());

                        int nrStudenti = 0;
                        std::cout << "\nCati studenti doriti sa adaugati in grup? ";
                        std::cin >> nrStudenti;
                        std::cin.ignore(10000, '\n');

                        for (int i = 0; i < nrStudenti; ++i) {
                            std::string numeS, prenumeS, emailS, scoalaS;
                            int varstaS, anStudiu;

                            std::cout << "\n- Date Student " << (i + 1) << " -\n";
                            std::cout << "Nume: "; std::getline(std::cin, numeS);
                            std::cout << "Prenume: "; std::getline(std::cin, prenumeS);
                            std::cout << "Varsta: "; std::cin >> varstaS; std::cin.ignore(10000, '\n');
                            std::cout << "Email: "; std::getline(std::cin, emailS);
                            std::cout << "Scoala: "; std::getline(std::cin, scoalaS);
                            std::cout << "An de studiu: "; std::cin >> anStudiu; std::cin.ignore(10000, '\n');

                            try {
                                grupNou->addMember(new Student(numeS, prenumeS, varstaS, emailS, new DiscountTicket(30.0, "RON", 0.5), scoalaS, anStudiu));
                            } catch (const std::exception& e) {
                                std::cout << "[EROARE LA ADAUGARE STUDENT] " << e.what() << "\n";
                            }
                        }

                        std::string descriereCerere = "Prof. " + profesorLogat->getName() + " solicita vizita. Ghid solicitat: ";
                        if (raspunsGhid == "da" || raspunsGhid == "DA" || raspunsGhid == "Da") {
                            descriereCerere += "DA";
                        } else {
                            descriereCerere += "NU";
                        }
                        descriereCerere += " [REF:" + profesorLogat->getEmail() + "]";

                        Cerere nouaCerere(urmatorulIdCerere++, "PROGRAMARE", grupNou, "", descriereCerere);
                        cereriInAsteptare.push_back(nouaCerere);
                        std::cout << "\n[SUCCES] Solicitarea a fost trimisa administratorului spre aprobare!\n";
                        break;
                    }
                    case 3: {
                        std::cout << "\n--- SOLICITARE ANULARE BILET STUDENT ---\n";
                        if (grupAsociatUtilizator == nullptr) {
                            std::cout << "[EROARE LOGICA] Nu aveti niciun grup aprobat activ din care sa eliminati studenti!\n";
                            break;
                        }

                        Date azi = Date::getToday();
                        if (!(azi < grupAsociatUtilizator->getDataVizitei())) {
                            std::cout << "[REFUZAT] Eroare politica anulare! Nu puteti modifica componenta grupului in ziua vizitei.\n";
                            break;
                        }

                        std::cout << "Introduceti email-ul studentului care nu mai poate veni: ";
                        std::string emailStergere; std::getline(std::cin, emailStergere);

                        if (!grupAsociatUtilizator->areMembru(emailStergere)) {
                            std::cout << "[EROARE LOGICA] Studentul cu email-ul " << emailStergere << " nu exista in grupul dumneavoastra! Cererea a fost respinsa automat.\n";
                            break;
                        }

                        Cerere nouaCerere(urmatorulIdCerere++, "ANULARE_STUDENT", grupAsociatUtilizator, emailStergere, "Solicitare eliminare student cu email: " + emailStergere + " [REF:" + profesorLogat->getEmail() + "]");
                        cereriInAsteptare.push_back(nouaCerere);
                        std::cout << "[SUCCES] Cererea de stergere a fost trimisa administratorului.\n";
                        break;
                    }
                    case 4: {
                        std::cout << "\n--- SOLICITARE ANULARE COMPLETA GRUP ---\n";
                        if (grupAsociatUtilizator == nullptr) {
                            std::cout << "[EROARE LOGICA] Nu aveti o programare activa salvata pe care sa o puteti anula!\n";
                            break;
                        }

                        Date azi = Date::getToday();
                        if (!(azi < grupAsociatUtilizator->getDataVizitei())) {
                            std::cout << "[REFUZAT] Nu puteti anula vizita in aceeasi zi! Trebuie anulata cu minim o zi inainte.\n";
                            break;
                        }

                        Cerere nouaCerere(urmatorulIdCerere++, "ANULARE_GRUP", grupAsociatUtilizator, "", "Solicitare anulare completa grup [REF:" + profesorLogat->getEmail() + "]");
                        cereriInAsteptare.push_back(nouaCerere);
                        std::cout << "[SUCCES] Solicitarea a fost trimisa catre administrator.\n";
                        break;
                    }
                    case 5: {
                        std::cout << "\n--- STATUS SI NOTIFICARI ---\nStatus cont: ";
                        if (grupAsociatUtilizator != nullptr) std::cout << "PROGRAMARE CONFIRMATA in data de " << grupAsociatUtilizator->getDataVizitei() << "\n";
                        else std::cout << "IN ASTEPTARE SAU FARA PROGRAMARI.\n";

                        std::cout << "\n--- Mesaje de la Administrator ---\n";
                        bool gasitMesaje = false;
                        for (const auto& n : cutiePostalaNotificari) {
                            if (n.emailProfesor == profesorLogat->getEmail()) {
                                std::cout << ">> " << n.textMesaj << "\n";
                                gasitMesaje = true;
                            }
                        }
                        if (!gasitMesaje) {
                            std::cout << "Nu aveti mesaje noi.\n";
                        }
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

    for (Professor* p : conturiProfesori) {
        bool dejaSters = false;
        for (Group* g : toateGrupurileAprobate) {
            if (g->areMembru(p->getEmail())) {
                dejaSters = true;
                break;
            }
        }
        if (!dejaSters) delete p;
    }

    std::cout << "\n--- Program Finalizat cu Succes ---\n";
    return 0;
}