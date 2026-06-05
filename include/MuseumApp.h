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
#include "Repository.h"

class MuseumApp {
private:
    Location loc;
    Museum antipa;
    TemporaryExhibition fluturi;
    InteractiveExhibition vr;

    Repository<Group*> toateGrupurileAprobate;
    std::vector<Cerere> cereriInAsteptare;
    Repository<Professor*> conturiProfesori;
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