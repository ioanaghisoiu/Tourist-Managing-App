#pragma once
#include <exception>

class GroupThresholdException : public std::exception {
public:
     [[nodiscard]]const char* what() const noexcept override;
};

class DuplicateEmailException : public std::exception {
public:
     [[nodiscard]]const char* what() const noexcept override;
};

class InvalidGroupStateException : public std::exception {
public:
     [[nodiscard]]const char* what() const noexcept override;
};

class WrongMuseumException : public std::exception {
public:
     const char* what() const noexcept override;
};

class PersonNotExistsException : public std::exception {
public:
     [[nodiscard]] const char* what() const noexcept override {
          return "PersonNotExistsException: Persoana nu a fost gasita in grup.";
     }
};