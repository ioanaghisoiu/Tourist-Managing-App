#pragma once
#include <exception>

class GroupThresholdException : public std::exception {
public:
    const char* what() const noexcept override;
};