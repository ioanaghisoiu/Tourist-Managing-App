#pragma once
#include <iostream>
#include <string>

class Exhibition {
protected:
    std::string title;
    double extraFee;
    int itemsCount;
public:
    explicit Exhibition(std::string title_ = "Expozitie Generica", double fee_ = 0.0, int items_ = 0);

    [[nodiscard]] bool isPremiumExhibition() const;
    bool operator<(const Exhibition& other) const;
    [[nodiscard]] int getEstimatedVisitTime() const;
    [[nodiscard]] double getExtraFee() const;
    [[nodiscard]] int getItemsCount() const;
    [[nodiscard]] const std::string& getTitle() const;

    void setTitle(const std::string& newTitle);
    void updatePrice(double newFee);
    void addItems(int count);

    Exhibition& operator+=(int newItems);

    friend std::ostream& operator<<(std::ostream& os, const Exhibition& ex);
    friend std::istream& operator>>(std::istream& is, Exhibition& ex);

    virtual ~Exhibition() = default;

    virtual void print(std::ostream& os) const;

};