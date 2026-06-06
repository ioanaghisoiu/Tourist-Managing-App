#pragma once
#include <iostream>
#include <vector>
#include "Person.h"
#include "Exceptions.h"
#include "Date.h"
#include "Countable.h"

class Group : public Countable<Group> {
private:
    std::vector<Person*> members;
    Person* guide;
    long museum_code;
    std::string museum_name;
    [[nodiscard]] bool isEmailDuplicate(const std::string& email) const;
    Date dataVizitei;
    bool optiuneVR = false;

public:
    Group(const std::string& museum_name_, long museum_code_,const Date& data_);

    ~Group();
    Group(const Group& other);
    Group& operator=(const Group& other);

    void setGuide(Person* newGuide);
    void addMember(Person* member);


    [[nodiscard]] bool isReadyForVisit() const;

    [[nodiscard]] double calculateTotalRevenue() const;

    void sortMembersByAge();

    long getMuseumCode() const { return museum_code; }

    [[nodiscard]] const Date& getDataVizitei() const { return dataVizitei; }

    void removeMember(const std::string& emailStergere);

    friend std::ostream& operator<<(std::ostream& os, const Group& g);

    bool areMembru(const std::string& emailCautat) const;

    void setDataVizitei(const Date& nouaData);

    void setVR(bool vr) { optiuneVR = vr; }
    bool hasVR() const { return optiuneVR; }

    void monitorizeazaActivitateLive() const;
};