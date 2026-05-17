#pragma once
#include <iostream>
#include <string>
#include "Ticket.h"

class Person {
private:
    std::string name;
    std::string surname;
    int age;
    std::string email;
    Ticket ticket;
public:
    Person(const std::string& name_, const std::string& surname_, int age_,
           const std::string& email_, double tPrice);
    void validateEmail() const;
    const std::string& getName() const;
    const std::string& getEmail() const;
    int getAge() const;
    void setName(const std::string& newName);
    void setSurname(const std::string& newSurname);
    void setEmail(const std::string& newEmail);
    void setAge(int newAge);
    bool isMinor() const;
    bool operator==(const Person& other) const;
    bool operator!=(const Person& other) const;
    bool operator<(const Person& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
};