#include "NotificationCenter.h"

void NotificationCenter::subscribe(const std::string& email, IObserver* observer) {
    observatori[email] = observer;
}

void NotificationCenter::unsubscribe(const std::string& email) {
    observatori.erase(email);
}

void NotificationCenter::notify(const std::string& email, const std::string& mesaj) {
    auto it = observatori.find(email);
    if (it != observatori.end())
        it->second->onNotificare(mesaj);
}

void NotificationCenter::notifyAll(const std::string& mesaj) {
    for (auto& [email, obs] : observatori)
        obs->onNotificare(mesaj);
}