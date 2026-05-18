#pragma once
#include "Person.h"

class Professor : public Person {
private:
    int experience;
    std::string school;

protected:
    void afisare(std::ostream& os) const override;

public:
    Professor(const std::string& surname_, const std::string& name_, int age_,
              const std::string& email_,double tPrice, int experience_, const std::string& school_);

    [[nodiscard]] Person* clone() const override;
    [[nodiscard]] std::string getRole() const override { return "Profesor"; }

    void receiveNotification(const std::string& museumName, long museumCode, const std::string& message) const;
    [[nodiscard]] double getTicketDiscount() const override { return 0.2; }
};