#pragma once
#include "Person.h"

class Student: public Person {
private:
    std::string school;
    int studyYear;

protected:
    void afisare(std::ostream& os) const override;

public:
    Student(const std::string& surname_, const std::string& name_, int age_,
            const std::string& email_,double tPrice, const std::string& school_, int studyYear_);

    [[nodiscard]] Person* clone() const override;

   [[nodiscard]] std::string getRole() const override { return "Student"; }
    [[nodiscard]] double getTicketDiscount() const override { return 0.5; }

};