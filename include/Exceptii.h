//
// Created by razvan on 5/23/25.
//

#ifndef EXCEPTII_H
#define EXCEPTII_H
#include <exception>


class RaritateInvalida: public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override{
        return "Raritate invalida";

    }
};

class EnergiePutina: public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Energie insuficienta";
    }
};

class EnergieMulta : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Prea multa energie";
    }
};
class RasaInvalida: public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Rasa invalida";
    }
};
class BaniInsuficienti: public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Bani insuficienti";
    }
};


#endif //EXCEPTII_H
