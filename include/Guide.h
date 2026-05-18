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

    Guide(const std::string& name_, const std::string& surname_, int age_, const std::string& email_, Ticket* ticket_,
          const std::string& foreignLanguage_, int badgeNumber_);


    [[nodiscard]] Person* clone() const override;


    [[nodiscard]] std::string getRole() const override { return "Ghid"; }

    [[nodiscard]] std::string getForeignLanguage() const { return foreignLanguage; }
    [[nodiscard]] int getBadgeNumber() const { return badgeNumber; }
    double getTicketDiscount() const override;
};