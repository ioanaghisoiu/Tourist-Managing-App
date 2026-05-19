#pragma once
#include "Exhibition.h"
#include "IInteractive.h"
#include <string>

class InteractiveExhibition : public Exhibition, public IInteractive {
private:
    std::string deviceType;

public:
    InteractiveExhibition(const std::string& title_, double fee_, int items_, const std::string& deviceType_);
    
    void print(std::ostream& os) const override;
    

    void interact() const override; 
};