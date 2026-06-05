#pragma once
#include <string>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onNotificare(const std::string& mesaj) = 0;
};