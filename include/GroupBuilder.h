#pragma once
#include "Group.h"

class GroupBuilder {
    std::string museumName;
    long museumCode = 0;
    Date date;
    bool vrEnabled = false;

public:
    GroupBuilder(const std::string& name, long code, const Date& d)
        : museumName(name), museumCode(code), date(d) {}

    GroupBuilder& withVR(bool vr) { vrEnabled = vr; return *this; }

    [[nodiscard]] Group* build() const {
        Group* g = new Group(museumName, museumCode, date);
        g->setVR(vrEnabled);
        return g;
    }
};