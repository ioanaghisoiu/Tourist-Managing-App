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
#include <fstream>

class MesajNotificare {
public:
    std::string emailProfesor;
    std::string textMesaj;
};

void afiseazaMeniuUtilizator() {
    std::cout << "\nMENIU UTILIZATOR\n";
    std::cout << "1. Vizualizeaza Muzeu si Expozitii disponibile\n";
    std::cout << "2. Trimite cerere de programare vizita noua \n";
    std::cout << "3. Trimite cerere de anulare bilet pentru un student \n";
    std::cout << "4. Trimite cerere de anulare completa a grupului \n";
    std::cout << "5. Vizualizeaza status programare si notificari primite\n";
    std::cout << "6. Editeaza datele profilului tau si reprogramare vizita\n";
    std::cout << "0. Iesire din cont \n";
    std::cout << "Alege o optiune: ";
}

void afiseazaMeniuAdministrator() {
    std::cout << "\nMENIU ADMINISTRATOR\n";
    std::cout << "1. Vizualizeaza cererile trimise de profesori \n";
    std::cout << "2. Aproba si executa urmatoarea cerere din lista \n";
    std::cout << "3. Afiseaza toate grupurile aprobate din sistem \n";
    std::cout << "4. Raport vizite in fisier\n";
    std::cout << "5. Statistici administrative si management locatie muzeu\n";
    std::cout << "6. Administrare si modificare expozitii active\n";
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

    std::cout << "TOURIST MANAGING APP \n";
    std::cout << "Data curenta a sistemului: " << Date::getToday() << "\n\n";

    std::string rolCurent = "";
    while (true) {
        std::cout << "Sunteti administrator sau utilizator? (Scrieti exact rolul sau 'iesire'): ";

        if (!std::getline(std::cin, rolCurent)) break;

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
                        std::cout << "\nCERERI IN ASTEPTARE DE LA UTILIZATORI\n";
                        if (cereriInAsteptare.empty()) {
                            std::cout << "Nu exista cereri noi in acest moment.\n";
                        } else {
                            for (const auto& c : cereriInAsteptare) {
                                std::cout << " ID Cerere: [" << c.getId() << "] | Tip: " << c.getTip() << "\n";
                                std::cout << " Descriere: " << c.getDescriere() << "\n";
                            }
                        }
                        break;
                    }
                    case 2: {
                        std::cout << "\nPROCESARE SI APROBARE CERERE\n";
                        if (cereriInAsteptare.empty()) {
                            std::cout << "Nu exista nicio cerere de procesat.\n";
                            break;
                        }

                        Cerere c = cereriInAsteptare.front();
                        cereriInAsteptare.erase(cereriInAsteptare.begin());

                        std::string emailProfAsociat = "";
                        if (c.getGrupAsociat()) {

                            for (const Professor* p : conturiProfesori) {
                                if (c.getGrupAsociat()->areMembru(p->getEmail())) {
                                    emailProfAsociat = p->getEmail();
                                    break;
                                }
                            }
                        }

                        if (c.getTip() == "PROGRAMARE") {
                            if (c.getDescriere().find("Ghid: DA") != std::string::npos) {

                                Guide* ghidAlocat = new Guide("Elena", "Ghidul", 28, "elena@muzeu.ro", new Ticket(0.0, "RON", false), "Engleza", 999);
                                std::cout << "Alocare ghid cu ecusonul nr. " << ghidAlocat->getBadgeNumber()
                                          << " pentru limba " << ghidAlocat->getForeignLanguage() << ".\n";

                                c.getGrupAsociat()->setGuide(ghidAlocat);
                                std::cout << "Cererea a fost aprobata cu GHID alocat!\n";
                            } else {
                                c.getGrupAsociat()->setGuide(nullptr);
                                std::cout << "Cererea a fost aprobata ca TUR LIBER!\n";
                            }

                            if (c.getGrupAsociat()->hasVR()) {
                                std::cout << "Sistemul deblocheaza echipamentele VR pentru acest grup...\n";
                                vr.interact();
                            }

                            toateGrupurileAprobate.push_back(c.getGrupAsociat());
                            try { antipa.hostGroupVisit(*(c.getGrupAsociat())); } catch (...) {}
                            (void)c.getGrupAsociat()->isReadyForVisit();

                            MesajNotificare notif;
                            notif.emailProfesor = emailProfAsociat;
                            notif.textMesaj = "Cererea de programare a fost aprobata!";
                            cutiePostalaNotificari.push_back(notif);
                        }
                        else if (c.getTip() == "ANULARE_STUDENT") {
                            try {
                                c.getGrupAsociat()->removeMember(c.getEmailTinta());
                                std::cout << "Studentul a fost eliminat.\n";
                                double totalNou = c.getGrupAsociat()->calculateTotalRevenue();

                                MesajNotificare notif;
                                notif.emailProfesor = emailProfAsociat;
                                notif.textMesaj = "Student sters. Nou total: " + std::to_string(totalNou) + " RON.";
                                cutiePostalaNotificari.push_back(notif);
                            } catch (const std::exception& e) {
                                std::cout << "[EROARE] " << e.what() << "\n";
                            }
                        }
                        else if (c.getTip() == "ANULARE_GRUP") {
                            auto it = toateGrupurileAprobate.begin();
                            while (it != toateGrupurileAprobate.end()) {
                                if (*it == c.getGrupAsociat()) {
                                    MesajNotificare notif;
                                    notif.emailProfesor = emailProfAsociat;
                                    notif.textMesaj = "Anulare completa aprobata.";
                                    cutiePostalaNotificari.push_back(notif);

                                    delete *it;
                                    toateGrupurileAprobate.erase(it);
                                    break;
                                }
                                ++it;
                            }
                            std::cout << "Grup anulat.\n";
                        }
                        break;
                    }
                    case 3: {
                        std::cout << "\nVIZUALIZARE PROGRAMARI DUPA DATA \nIntroduceti data:\n";
                        Date dt; std::cin >> dt;
                        bool gasit = false;

                        for (Group* g : toateGrupurileAprobate) {
                            if (g->getDataVizitei() == dt) {
                                g->sortMembersByAge();
                                std::cout << "\n[GRUP PROGRAMAT IN DATA DE " << dt << "]:\n" << *g;
                                gasit = true;
                            }
                        }
                        if (!gasit) std::cout << "Nu exista grupuri aprobate.\n";
                        break;
                    }
                    case 4: {
                        std::cout << "\nEXPORT RAPORT VIZITE IN FISIER\n";
                        if (toateGrupurileAprobate.empty()) {
                            std::cout << "Nu exista grupuri aprobate.\n";
                            break;
                        }

                        std::ofstream fout("raport_vizite.txt");
                        if (!fout.is_open()) {
                            std::cout << "[EROARE] Nu s-a putut crea fisierul!\n";
                            break;
                        }

                        fout << "RAPORT MANAGER - VIZITE MUZEE\n";
                        fout << "Total grupuri programate: " << toateGrupurileAprobate.size() << "\n\n";
                        double profitTotalEstimativ = 0.0;

                        for (size_t i = 0; i < toateGrupurileAprobate.size(); ++i) {
                            const Group* g = toateGrupurileAprobate[i];
                            fout << "Grupul #" << (i + 1) << ":\n";
                            fout << "  - Cod Muzeu Vizitat: " << g->getMuseumCode() << "\n";
                            fout << "  - Data programata: " << g->getDataVizitei() << "\n";
                            fout << "  - A solicitat VR: " << (g->hasVR() ? "DA" : "NU") << "\n";

                            try {
                                double venitGrup = g->calculateTotalRevenue();
                                profitTotalEstimativ += venitGrup;
                                fout << "  - Venit estimat grup: " << venitGrup << " RON\n";
                            } catch (...) {
                                fout << "  - Venit estimat grup: EROARE CALCUL\n";
                            }
                        }
                        fout << " TOTAL VENITURI: " << profitTotalEstimativ << " RON\n";
                        fout.close();
                        std::cout << "Export cu succes in 'raport_vizite.txt'!\n";
                        break;
                    }
                    case 5: {

                        std::cout << "\nSTATISTICI ADMINISTRATIVE SI MANAGEMENT LOCATIE\n";
                        std::cout << "Total muzee inregistrate in sistem: " << Museum::getTotalMuseums() << "\n";
                        std::cout << "Codul unic al muzeului curent: " << antipa.getCode() << "\n";
                        std::cout << "Codul SIRUTA al locatiei: " << loc.getSirutaCode() << "\n";
                        std::cout << "Venituri totale raportate de muzeu: " << antipa.getTotalRevenue() << " RON\n";
                        std::cout << "Doriti sa actualizati adresa fizica a muzeului? (da/nu): ";
                        std::string raspAdresa; std::getline(std::cin, raspAdresa);
                        if (raspAdresa == "da" || raspAdresa == "DA") {
                            std::cout << "Introduceti noua adresa: ";
                            std::string adresaNoua; std::getline(std::cin, adresaNoua);
                            loc.updateAddress(adresaNoua);
                            std::cout << "Adresa a fost actualizata!\n";
                        }
                        break;
                    }
                    case 6: {

                        std::cout << "\nADMINISTRARE EXPOZITII\n";
                        std::cout << "1. Modifica titlul expozitiei temporare\n";
                        std::cout << "2. Actualizeaza pretul expozitiei temporare\n";
                        std::cout << "3. Adauga elemente noi in expozitia VR\n";
                        std::cout << "Alege o optiune: ";
                        int optExp; std::cin >> optExp; std::cin.ignore(10000, '\n');
                        if (optExp == 1) {
                            std::cout << "Nou titlu: "; std::string titluNou; std::getline(std::cin, titluNou);
                            fluturi.setTitle(titluNou);
                            std::cout << "Titlu modificat.\n";
                        } else if (optExp == 2) {
                            std::cout << "Noua taxa: "; double taxaNoua; std::cin >> taxaNoua; std::cin.ignore(10000, '\n');
                            fluturi.updatePrice(taxaNoua);
                            std::cout << "Pret actualizat.\n";
                        } else if (optExp == 3) {
                            std::cout << "Numar obiecte de adaugat: "; int nrObiecte; std::cin >> nrObiecte; std::cin.ignore(10000, '\n');
                            vr.addItems(nrObiecte);
                            std::cout << "Obiecte adaugate.\n";
                        }
                        break;
                    }
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

            for (const Professor* p : conturiProfesori) {
                if (p->getEmail() == emailUtilizatorCurent) { profesorLogat = const_cast<Professor*>(p); break; }
            }

            if (profesorLogat == nullptr) {
                std::cout << "\nCREARE CONT NOU PROFESOR\n";
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


            if (profesorLogat->isMinor()) {
                std::cout << "Atentie: Profil de cadru didactic incadrat la categoria minori.\n";
            }

            int optUtilizator = -1;
            while (optUtilizator != 0) {
                afiseazaMeniuUtilizator();
                std::cin >> optUtilizator;

                Group* grupAsociatUtilizator = nullptr;
                for (const Group* g : toateGrupurileAprobate) {
                    if (g->areMembru(profesorLogat->getEmail())) { grupAsociatUtilizator = const_cast<Group*>(g); break; }
                }
                std::cin.ignore(10000, '\n');

                switch (optUtilizator) {
                    case 1: {
                        std::cout << "\nLOCATIE SISTEM CENTRAL\n";
                        std::cout << loc << "\n";

                        std::cout << "\n" << antipa << "\n" << fluturi << "\n" << vr << "\n";


                        std::cout << "DETALII SUPLIMENTARE EXPOZITII\n";
                        std::cout << "Timp estimat de vizitare expozitie temporara: " << fluturi.getEstimatedVisitTime() << " minute.\n";
                        std::cout << "Taxa suplimentara perceputa: " << fluturi.getExtraFee() << " RON.\n";
                        if (fluturi.isPremiumExhibition()) {
                            std::cout << "[PREMIUM] Aceasta expozitie este catalogata ca eveniment Premium.\n";
                        }
                        std::cout << "\nCautati o expozitie anume in catalog? Introduceti titlul exact: ";
                        std::string titluCautat; std::getline(std::cin, titluCautat);

                        if (antipa.hasExhibition(titluCautat) || fluturi.getTitle() == titluCautat || vr.getTitle() == titluCautat) {
                            std::cout << "Expozitia '" << titluCautat << "' este deschisa publicului!\n";
                        } else {
                            std::cout << "Expozitia cautata nu se afla in acest muzeu.\n";
                        }
                        break;
                    }
                    case 2: {
                        std::cout << "\nSOLICITARE PROGRAMARE VIZITA NOUA\n";
                        if (grupAsociatUtilizator != nullptr) {
                            std::cout << "Aveti deja o vizita activa!\n";
                            break;
                        }

                        std::cout << "Introduceti data (Zi Luna An):\n";
                        Date dataDorita; std::cin >> dataDorita; std::cin.ignore(10000, '\n');

                        if (!dataDorita.isValid()) {
                            std::cout << "Data invalida!\n";
                            break;
                        }

                        std::string raspunsGhid, raspunsVR;
                        std::cout << "\nTur cu ghid? (da/nu): ";
                        std::getline(std::cin, raspunsGhid);

                        std::cout << "Doriti acces la echipamentele interactive VR (taxa suplimentara)? (da/nu): ";
                        std::getline(std::cin, raspunsVR);

                        Group* grupNou = new Group("Muzeul Grigore Antipa", 101, dataDorita);
                        grupNou->addMember(profesorLogat->clone());

                        if (raspunsVR == "da" || raspunsVR == "DA" || raspunsVR == "Da") {
                            grupNou->setVR(true);
                        }

                        int nrStudenti = 0;
                        std::cout << "\nCati studenti: ";
                        std::cin >> nrStudenti; std::cin.ignore(10000, '\n');

                        for (int i = 0; i < nrStudenti; ++i) {
                            std::string numeS, prenumeS, emailS, scoalaS;
                            int varstaS, anStudiu;

                            std::cout << "\nDate Student " << (i + 1) << "\nNume: "; std::getline(std::cin, numeS);
                            std::cout << "Prenume: "; std::getline(std::cin, prenumeS);
                            std::cout << "Varsta: "; std::cin >> varstaS; std::cin.ignore(10000, '\n');
                            std::cout << "Email: "; std::getline(std::cin, emailS);
                            std::cout << "Scoala: "; std::getline(std::cin, scoalaS);
                            std::cout << "An de studiu: "; std::cin >> anStudiu; std::cin.ignore(10000, '\n');

                            try {
                                grupNou->addMember(new Student(numeS, prenumeS, varstaS, emailS, new DiscountTicket(30.0, "RON", 0.5), scoalaS, anStudiu));
                            } catch (const std::exception& e) {
                                std::cout << "[EROARE] " << e.what() << "\n";
                            }
                        }

                        std::string decizieGhid = (raspunsGhid == "da" || raspunsGhid == "DA" || raspunsGhid == "Da") ? "DA" : "NU";
                        std::string descriereCerere = "Prof. " + profesorLogat->getName() + " solicita vizita. Ghid: " + decizieGhid;
                        descriereCerere += (grupNou->hasVR() ? " | Extra: Echipament VR" : "");

                        Cerere nouaCerere(urmatorulIdCerere++, "PROGRAMARE", grupNou, "", descriereCerere);
                        cereriInAsteptare.push_back(nouaCerere);
                        std::cout << "\nSolicitare trimisa!\n";
                        break;
                    }
                    case 3: {
                        std::cout << "\nANULARE BILET STUDENT\n";
                        if (grupAsociatUtilizator == nullptr) {
                            std::cout << "Nu aveti grup aprobat.\n"; break;
                        }
                        if (!(Date::getToday() < grupAsociatUtilizator->getDataVizitei())) {
                            std::cout << "Eroare politica anulare.\n"; break;
                        }
                        std::cout << "Email-ul studentului: ";
                        std::string emailStergere; std::getline(std::cin, emailStergere);

                        if (!grupAsociatUtilizator->areMembru(emailStergere)) {
                            std::cout << "Studentul nu exista in grup.\n"; break;
                        }

                        Cerere nouaCerere(urmatorulIdCerere++, "ANULARE_STUDENT", grupAsociatUtilizator, emailStergere, "Solicitare stergere student din grup.");
                        cereriInAsteptare.push_back(nouaCerere);
                        std::cout << "Cerere stergere trimisa.\n";
                        break;
                    }
                    case 4: {
                        std::cout << "\nANULARE COMPLETA GRUP\n";
                        if (grupAsociatUtilizator == nullptr) {
                            std::cout << "Nu aveti programare activa.\n"; break;
                        }
                        if (!(Date::getToday() < grupAsociatUtilizator->getDataVizitei())) {
                            std::cout << "Eroare politica anulare.\n"; break;
                        }

                        Cerere nouaCerere(urmatorulIdCerere++, "ANULARE_GRUP", grupAsociatUtilizator, "", "Solicitare anulare completa a excursiei.");
                        cereriInAsteptare.push_back(nouaCerere);
                        std::cout << "Solicitare trimisa.\n";
                        break;
                    }
                    case 5: {
                        std::cout << "\nSTATUS SI NOTIFICARI\nStatus: ";
                        if (grupAsociatUtilizator != nullptr) std::cout << "CONFIRMATA: " << grupAsociatUtilizator->getDataVizitei() << "\n";
                        else std::cout << "IN ASTEPTARE.\n";

                        std::cout << "\nMesaje de la Administrator\n";
                        bool gasitMesaje = false;
                        for (const auto& n : cutiePostalaNotificari) {
                            if (n.emailProfesor == profesorLogat->getEmail()) {
                                std::cout << ">> " << n.textMesaj << "\n";
                                gasitMesaje = true;
                            }
                        }
                        if (!gasitMesaje) std::cout << "Nu aveti mesaje noi.\n";
                        break;
                    }
                    case 6: {
                        std::cout << "\nEDITARE PROFIL SI REPROGRAMARE\n";
                        std::string emailC = profesorLogat->getEmail();
                        std::string nN, pN, eN, vS;

                        std::cout << "Nume nou (Enter pt a pastra): "; std::getline(std::cin, nN);
                        std::cout << "Prenume nou (Enter pt a pastra): "; std::getline(std::cin, pN);
                        std::cout << "Email nou (Enter pt a pastra): "; std::getline(std::cin, eN);
                        std::cout << "Varsta noua (Enter pt a pastra): "; std::getline(std::cin, vS);

                        if (!nN.empty()) profesorLogat->setName(nN);
                        if (!pN.empty()) profesorLogat->setSurname(pN);
                        if (!eN.empty()) profesorLogat->setEmail(eN);
                        if (!vS.empty()) { try { profesorLogat->setAge(std::stoi(vS)); } catch (...) {} }

                        Group* gr = grupAsociatUtilizator;
                        if (!gr) {
                            for (const auto& c : cereriInAsteptare) {
                                if (c.getGrupAsociat() && c.getGrupAsociat()->areMembru(emailC)) {
                                    gr = c.getGrupAsociat(); break;
                                }
                            }
                        }

                        if (gr) {
                            std::string rasp;
                            std::cout << "\nReprogramati vizita? (da/nu): "; std::getline(std::cin, rasp);
                            if (rasp == "da" || rasp == "DA") {
                                std::cout << "Noua data (Zi Luna An):\n";
                                Date dataNoua; std::cin >> dataNoua; std::cin.ignore(10000, '\n');
                                if (dataNoua.isValid()) {
                                    gr->setDataVizitei(dataNoua);
                                    std::cout << "Reprogramata!\n";
                                } else std::cout << "Data invalida.\n";
                            }
                        }
                        std::cout << "Profil actualizat!\n";
                        break;
                    }
                }
            }
        }
        else {
            std::cout << "OPTIUNE INVALIDA\n\n";
        }
    }

    for (Group* g : toateGrupurileAprobate) delete g;

    for (const auto& c : cereriInAsteptare) {
        if (c.getTip() == "PROGRAMARE") delete c.getGrupAsociat();
    }

    for (Professor* p : conturiProfesori) {
        bool dejaSters = false;
        for (const Group* g : toateGrupurileAprobate) {
            if (g->areMembru(p->getEmail())) {
                dejaSters = true;
                break;
            }
        }
        if (!dejaSters) delete p;
    }

    std::cout << "\nProgram Finalizat\n";
    return 0;
}