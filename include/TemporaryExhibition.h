#pragma once
#include "Exhibition.h"

class TemporaryExhibition : public Exhibition {
private:
    int daysRemaining;

public:
    TemporaryExhibition(const std::string& title_, double fee_, int items_, int daysRemaining_);
    
    void print(std::ostream& os) const override;
};