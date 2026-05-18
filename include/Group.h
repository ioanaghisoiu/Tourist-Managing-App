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
    [[nodiscard]] bool isEmailDuplicate(const std::string& email) const;
public:
    Group(const std::string& museum_name_, long museum_code_);

    ~Group();
    Group(const Group& other);
    Group& operator=(const Group& other);

    void setGuide(Person* newGuide);
    void addMember(Person* member);

    [[nodiscard]]double calculateAverageAge() const;
    [[nodiscard]] bool isReadyForVisit() const;

    [[nodiscard]] double calculateTotalRevenue() const;

    void sortMembersByAge();
    int countMinors() const;

    long getMuseumCode() const { return museum_code; }

    friend std::ostream& operator<<(std::ostream& os, const Group& g);
};