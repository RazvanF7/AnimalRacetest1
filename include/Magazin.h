//
// Created by razvan on 5/23/25.
//

#ifndef MAGAZIN_H
#define MAGAZIN_H

#include <vector>
#include <memory>
#include "Animal.h"
#include "Jucator.h"

class Magazin {
    Magazin() = default;
    ~Magazin() = default;
    std::vector<std::shared_ptr<Animal>> inventar{};

public:
    static Magazin& instanta();
    Magazin(const Magazin&) = delete;
    Magazin& operator=(const Magazin&) = delete;

    void adaugaAnimal(std::shared_ptr<Animal> animal);
    void afisInventar() const;

    std::shared_ptr<Animal> cumparaAnimal(int id, const Jucator &cumparator);

};


#endif //MAGAZIN_H
