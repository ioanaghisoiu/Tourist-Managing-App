#pragma once
#include <iostream>
#include <vector>
#include "Person.h"
#include "Exceptions.h"

class Group {
private:
    std::vector<Person*> members;
    Person* guide;
    long museum_code;
    std::string museum_name;
    bool isEmailDuplicate(const std::string& email) const;
public:
    Group(const std::string& museum_name_, long museum_code_);

    ~Group();
    Group(const Group& other);
    Group& operator=(const Group& other);

    void setGuide(Person* newGuide);
    void addMember(Person* member);

    double calculateAverageAge() const;
    bool isReadyForVisit() const;

    double calculateTotalRevenue() const;

    friend std::ostream& operator<<(std::ostream& os, const Group& g);
};