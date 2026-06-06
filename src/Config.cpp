#include "Config.h"
#include "Exceptions.h"
#include <fstream>

Config Config::incarcaDinFisier(const std::string& cale) {
    Config c;
    std::ifstream fin(cale);
    if (!fin.is_open())
        throw ConfigFileException();

    std::string linie;
    while (std::getline(fin, linie)) {
        if (linie.empty() || linie[0] == '#') continue;
        auto pos = linie.find('=');
        if (pos == std::string::npos) continue;

        std::string cheie = linie.substr(0, pos);
        std::string valoare = linie.substr(pos + 1);

        if (cheie == "muzeu_nume") c.muzeulNume = valoare;
        else if (cheie == "muzeu_cod") c.muzeulCod = std::stoi(valoare);
        else if (cheie == "locatie_oras") c.locatieOras = valoare;
        else if (cheie == "locatie_adresa") c.locatieAdresa = valoare;
        else if (cheie == "locatie_siruta") c.locatieSiruta = std::stoi(valoare);
        else if (cheie == "parola_admin") c.parolaAdmin = valoare;
    }
    return c;
}