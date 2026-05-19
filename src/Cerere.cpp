#include "Cerere.h"

Cerere::Cerere(int id_, const std::string& tip_, Group* grup_, const std::string& email_, const std::string& desc_)
    : id(id_), tip(tip_), grupAsociat(grup_), emailTinta(email_), descriere(desc_) {}

int Cerere::getId() const { 
    return id; 
}

const std::string& Cerere::getTip() const { 
    return tip; 
}

Group* Cerere::getGrupAsociat() const { 
    return grupAsociat; 
}

const std::string& Cerere::getEmailTinta() const { 
    return emailTinta; 
}

const std::string& Cerere::getDescriere() const { 
    return descriere; 
}