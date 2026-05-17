#pragma once
#include <iostream>
#include <string>

class Exhibition {
private:
    std::string title;
    double extraFee;
    int itemsCount;
public:
    explicit Exhibition(std::string title_ = "Expozitie Generica", double fee_ = 0.0, int items_ = 0);
    bool isPremiumExhibition() const;
    bool operator<(const Exhibition& other) const;
    int getEstimatedVisitTime() const;
    double getExtraFee() const;
    int getItemsCount() const;
    const std::string& getTitle() const;
    void setTitle(const std::string& newTitle);
    void updatePrice(double newFee);
    void addItems(int count);
    friend std::ostream& operator<<(std::ostream& os, const Exhibition& ex);
    friend std::istream& operator>>(std::istream& is, Exhibition& ex);
};