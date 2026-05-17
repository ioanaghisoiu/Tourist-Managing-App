#pragma once
#include "Person.h"

class Student: public Person {
private:
    std:string school;
    int studyYear;

protected:
    void afisare(std::ostream& os) const override;

public:
    Student(const std::string& surname_, const std::string& name_, const std::string& role_, int age_,
            const std::string& email_, const std::string& school_, int studyYear_);

    Person* clone() const override;

    std::string getRole() const override { return "Student"; }

};