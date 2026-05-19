#pragma once
#include <string>
#include "Group.h"

class Cerere {
private:
    int id;
    std::string tip;
    Group* grupAsociat;
    std::string emailTinta;
    std::string descriere;

public:
    Cerere(int id_, const std::string& tip_, Group* grup_, const std::string& email_ = "", const std::string& desc_ = "");

    [[nodiscard]] int getId() const;
    [[nodiscard]] const std::string& getTip() const;
    [[nodiscard]] Group* getGrupAsociat() const;
    [[nodiscard]] const std::string& getEmailTinta() const;
    [[nodiscard]] const std::string& getDescriere() const;
};