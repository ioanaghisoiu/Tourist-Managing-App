#pragma once
#include <iostream>
#include <string>
#include "Ticket.h"

class Person {
protected:
    std::string name;
    std::string surname;
    int age;
    std::string email;
    Ticket ticket;

    virtual void afisare(std::ostream& os) const;
public:
    Person(const std::string& name_, const std::string& surname_, int age_,
           const std::string& email_, double tPrice);

    virtual ~Person() = default;
    virtual Person* clone() const = 0;
    [[nodiscard]] virtual std::string getRole() const = 0;

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

    [[nodiscard]] virtual double getTicketDiscount() const = 0;
};