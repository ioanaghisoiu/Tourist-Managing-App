#include "Exceptions.h"
 
const char* GroupThresholdException::what() const noexcept {
    return "GroupThresholdException: Grupul nu poate avea mai mult de 10 membri.";
}