#include "Student.h"

Student::Student(const std::string& name_, const std::string& surname_, int age_,
                 const std::string& email_, Ticket* ticket_,
                 const std::string& school_, int studyYear_)
    : Person(name_, surname_, age_, email_, ticket_), school(school_), studyYear(studyYear_) {}

Person* Student::clone() const {
    return new Student(*this);
}

void Student::afisare(std::ostream& os) const {
    os << name << " " << surname << " (" << age << " ani, Rol: " << getRole()
       << ", Scoala: " << school << ", An: " << studyYear<<")";
}