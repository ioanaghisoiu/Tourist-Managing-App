#include "Date.h"

Date::Date(int d, int m, int y)
    : ymd(std::chrono::year{y} / std::chrono::month{static_cast<unsigned>(m)}
          / std::chrono::day{static_cast<unsigned>(d)}) {}

bool Date::isValid() const { return ymd.ok(); }

bool Date::operator==(const Date& other) const { return ymd == other.ymd; }

std::ostream& operator<<(std::ostream& os, const Date& dt) {
    os << static_cast<unsigned>(dt.ymd.day()) << "/"
       << static_cast<unsigned>(dt.ymd.month()) << "/"
       << static_cast<int>(dt.ymd.year());
    return os;
}

std::istream& operator>>(std::istream& is, Date& dt) {
    int d, m, y;
    std::cout << "Zi: "; is >> d;
    std::cout << "Luna: "; is >> m;
    std::cout << "An: "; is >> y;
    dt = Date(d, m, y);
    return is;
}