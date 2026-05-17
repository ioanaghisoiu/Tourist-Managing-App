#pragma once
#include <iostream>
#include <string>

class Location {
private:
    std::string county;
    std::string address;
    int sirutaCode;
public:
    Location(std::string county_, std::string address_, int siruta_);
    Location();
    const std::string& getCounty() const;
    int getSirutaCode() const;
    void updateAddress(const std::string& newAddress);
    bool operator==(const Location& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Location& loc);
    friend std::istream& operator>>(std::istream& is, Location& loc);
};