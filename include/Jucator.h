//
// Created by razvan on 5/23/25.
//

#ifndef JUCATOR_H
#define JUCATOR_H


#include <string>
#include <vector>
#include <memory>
#include "Animal.h"

class Jucator{
    std::string nume;
    std::vector<std::shared_ptr<Animal>> inventarp{};
    int bani;
    int victorii;
    int popularitate;
public:
    Jucator(std::string nume, const std::vector <std::shared_ptr<Animal>>& invent);

    void adaugaAnimal(const std::shared_ptr<Animal>& animal);
    void afisInventar() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Animal>>& getAnimale() const;
    [[nodiscard]] int getBani()const;
    Jucator& operator-=(int suma);
    Jucator& operator+=(int suma);
    Jucator& operator++();
    void calcPop();
    [[nodiscard]] static std::string avantajPopular(const std::vector<std::shared_ptr<Animal>>& inventar) ;
    [[nodiscard]] int getPop()const;
};


#endif //JUCATOR_H
