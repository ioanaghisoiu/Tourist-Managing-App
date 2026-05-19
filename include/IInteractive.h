#pragma once
#include <iostream>

class IInteractive {
public:
    virtual ~IInteractive() = default;
    virtual void interact() const = 0; 
};