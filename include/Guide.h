#pragma once
#include "Person.h"
#include <string>

class Guide : public Person {
private:
    std::string foreignLanguage;
    int badgeNumber;

protected:
    void afisare(std::ostream& os) const override;

public:

    Guide(const std::string& name_, const std::string& surname_, int age_, const std::string& email_, double tPrice,
          const std::string& foreignLanguage_, int badgeNumber_);


    Person* clone() const override;


    std::string getRole() const override { return "Ghid"; }

    std::string getForeignLanguage() const { return foreignLanguage; }
    int getBadgeNumber() const { return badgeNumber; }
};