#pragma once
#include <iostream>
#include <vector>
#include "Person.h"
#include "Exceptions.h"

class Group {
private:
    std::vector<Person> persons;
    Person guide;
    long museum_code;
    bool isEmailDuplicate(const std::string& email) const;
public:
    Group(const std::vector<Person>& persons_, const Person& guide_, long museum_code_);
    void addMember(const Person& member);
    double calculateAverageAge() const;
    bool isReadyForVisit() const;
    double calculateTotalRevenue() const;
    friend std::ostream& operator<<(std::ostream& os, const Group& g);
};