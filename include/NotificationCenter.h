#pragma once
#include <string>
#include <map>
#include "IObserver.h"

class NotificationCenter {
private:
    std::map<std::string, IObserver*> observatori;
public:
    void subscribe(const std::string& email, IObserver* observer);
    void unsubscribe(const std::string& email);
    void notify(const std::string& email, const std::string& mesaj);
    void notifyAll(const std::string& mesaj);
};