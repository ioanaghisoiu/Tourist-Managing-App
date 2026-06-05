#pragma once
#include <vector>
#include <string>
#include "Person.h"
#include "IObserver.h"

class Professor : public Person, public IObserver {
private:
    int experience;
    std::string school;
    std::vector<std::string> mesajePrimite;

protected:
    void afisare(std::ostream& os) const override;

public:
    Professor(const std::string& name_, const std::string& surname_, int age_,
              const std::string& email_, Ticket* ticket_, int experience_, const std::string& school_);

    [[nodiscard]] Person* clone() const override;
    [[nodiscard]] std::string getRole() const override { return "Profesor"; }

    void receiveNotification(const std::string& museumName, long museumCode, const std::string& message) const;
    [[nodiscard]] double getTicketDiscount() const override { return 0.2; }

    void vizioneazaExpozitia() const override;

    void onNotificare(const std::string& mesaj) override;
    [[nodiscard]] const std::vector<std::string>& getMesaje() const;
};