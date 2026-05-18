#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Location.h"
#include "Exhibition.h"
#include "Group.h"


class Museum {
private:
    std::string name;
    long code;
    Location location;
    std::vector<Exhibition> exhibitions;
    std::vector<int> popularityVotes;
    static int totalMuseumsCreated;
    double totalRevenue;
public:
    Museum(std::string name_, long code_, Location loc_);

    static int getTotalMuseums();
    void addExhibition(const Exhibition& ex);
    void addVote(int score);

    [[nodiscard]] bool hasExhibition(const std::string& searchTitle) const;
    [[nodiscard]] int totalItems() const;
    [[nodiscard]] double averageVote() const;
    [[nodiscard]] long getCode() const;
    [[nodiscard]] const std::string& getName() const;

    double getTotalRevenue() const;
    void hostGroupVisit(Group& g);
    std::vector<Exhibition> getAffordableExhibitions(double maxBudget) const;



    friend std::ostream& operator<<(std::ostream& os, const Museum& m);
};