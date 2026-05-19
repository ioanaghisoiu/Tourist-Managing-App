#include "Exhibition.h"

Exhibition::Exhibition(std::string title_, double fee_, int items_)
    : title{std::move(title_)}, extraFee{fee_}, itemsCount{items_} {}

bool Exhibition::isPremiumExhibition() const { return extraFee > 50.0; }

bool Exhibition::operator<(const Exhibition& other) const {
    if (extraFee != other.extraFee) return extraFee < other.extraFee;
    return itemsCount < other.itemsCount;
}

int Exhibition::getEstimatedVisitTime() const { return itemsCount * 2; }
double Exhibition::getExtraFee() const { return extraFee; }
int Exhibition::getItemsCount() const { return itemsCount; }
const std::string& Exhibition::getTitle() const { return title; }

void Exhibition::setTitle(const std::string& newTitle) {
    if (!newTitle.empty()) title = newTitle;
}
void Exhibition::updatePrice(double newFee) {
    if (newFee >= 0) extraFee = newFee;
}
void Exhibition::addItems(int count) {
    if (count > 0) itemsCount += count;
}

std::ostream& operator<<(std::ostream& os, const Exhibition& ex) {
    ex.print(os);
    return os;
}


std::istream& operator>>(std::istream& is, Exhibition& ex) {
    std::cout << "Titlu expozitie: "; is.ignore(); std::getline(is, ex.title);
    std::cout << "Taxa extra: "; is >> ex.extraFee;
    std::cout << "Numar exponate: "; is >> ex.itemsCount;
    return is;
}

void Exhibition::print(std::ostream& os) const {
    os << "Expozitie: " << title << " | Taxa: " << extraFee << " RON | Obiecte: " << itemsCount;
}

Exhibition& Exhibition::operator+=(int newItems) {
    if (newItems > 0) {
        itemsCount += newItems;
    }
    return *this;
}