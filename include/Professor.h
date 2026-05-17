#pragma once
#include "Person.h"

class Professor : public Person {
private:
    int experience;
    std::string school;

protected:
    void afisare(std::ostream& os) const override;

public:
    Professor(const std::string& surname_, const std::string& name_, const std::string& role_, int age_,
              const std::string& email_, int experience_, const std::string& school_);

    Person* clone() const override;
    std::string getRole() const override { return "Profesor"; }


    void receiveNotification(const std::string& museumName, long museumCode, const std::string& message) const;
};