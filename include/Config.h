#pragma once
#include <string>

class Config {
    std::string muzeulNume;
    int muzeulCod = 0;
    std::string locatieOras;
    std::string locatieAdresa;
    int locatieSiruta = 0;
    std::string parolaAdmin;

    Config() = default;
public:
    static Config incarcaDinFisier(const std::string& cale);

    [[nodiscard]] const std::string& getMuzeulNume() const { return muzeulNume; }
    [[nodiscard]] int getMuzeulCod() const { return muzeulCod; }
    [[nodiscard]] const std::string& getLocatieOras() const { return locatieOras; }
    [[nodiscard]] const std::string& getLocatieAdresa() const { return locatieAdresa; }
    [[nodiscard]] int getLocatieSiruta() const { return locatieSiruta; }
    [[nodiscard]] const std::string& getParolaAdmin() const { return parolaAdmin; }
};