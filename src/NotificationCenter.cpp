#include "NotificationCenter.h"

void NotificationCenter::subscribe(const std::string& email, IObserver* observer) {
    observatori[email] = observer;
}

void NotificationCenter::notify(const std::string& email, const std::string& mesaj) {
    auto it = observatori.find(email);
    if (it != observatori.end())
        it->second->onNotificare(mesaj);
}