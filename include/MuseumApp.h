#pragma once
#include <vector>
#include <string>
#include "Location.h"
#include "Museum.h"
#include "Group.h"
#include "Professor.h"
#include "Cerere.h"
#include "TemporaryExhibition.h"
#include "InteractiveExhibition.h"
#include "NotificationCenter.h"

class MuseumApp {
private:
    Location loc;
    Museum antipa;
    TemporaryExhibition fluturi;
    InteractiveExhibition vr;

    std::vector<Group*> toateGrupurileAprobate;
    std::vector<Cerere> cereriInAsteptare;
    std::vector<Professor*> conturiProfesori;
    NotificationCenter notificationCenter;
    int urmatorulIdCerere;

    static void afiseazaMeniuUtilizator();
    static void afiseazaMeniuAdministrator();
    void handleAdministrator();
    void handleUtilizator();

public:
    MuseumApp();
    ~MuseumApp();
    void run();
};