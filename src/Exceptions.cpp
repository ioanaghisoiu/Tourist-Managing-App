#include "Exceptions.h"
 
const char* GroupThresholdException::what() const noexcept {
    return "GroupThresholdException: Grupul nu poate avea mai mult de 10 membri.";
}

const char* DuplicateEmailException::what() const noexcept {
    return "DuplicateEmailException: Acest email este deja inregistrat in grup. Fiecare membru trebuie sa aiba un email unic.";
}

const char* InvalidGroupStateException::what() const noexcept {
    return "InvalidGroupStateException: Operatiunea nu este permisa deoarece grupul nu este pregatit de vizita (verificati ghidul sau membrii).";
}

const char* WrongMuseumException::what() const noexcept {
    return "WrongMuseumException: Grupul are bilet pentru alt muzeu! Acces interzis.";
}