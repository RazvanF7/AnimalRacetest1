//
// Created by razvan on 5/23/25.
//

#include "../include/Jucator.h"
#include "../include/Caine.h"
#include "../include/Cal.h"
#include "../include/Exceptii.h"

#include <iostream>

Jucator::Jucator(std::string nume, const std::vector<std::shared_ptr<Animal>>& invent):
nume(std::move(nume)),bani(2000),victorii(0),popularitate(0) {
    for (auto const& i : invent) {
        inventarp.push_back(i->clone());
    }
}

Jucator& Jucator::operator-=(int suma) {
    if (bani < suma)
        throw BaniInsuficienti();
    bani -= suma;
    return *this;
}
Jucator& Jucator::operator+=(int suma) {
    bani += suma;
    return *this;
}
Jucator& Jucator::operator++() {
    victorii++;
    return *this;
}
int Jucator::getBani() const{
    return bani;
}
void Jucator::adaugaAnimal(const std::shared_ptr<Animal>& animal) {
    inventarp.push_back(animal->clone());
}

void Jucator::afisInventar() const {
    std::cout<<"animalele lui "<<nume<<std::endl;
    for (const auto& a: inventarp) {
        std::cout<<*a<<std::endl;
    }
    std::cout<<"popularitate: "<<popularitate << std::endl<<
        "victorii: "<<victorii << std::endl;
}

const std::vector<std::shared_ptr<Animal>>& Jucator::getAnimale() const {
    return inventarp;
}

void Jucator::calcPop() {
    int poplinit = 0;
    for (const auto& a : inventarp) {
        if (const auto caine = std::dynamic_pointer_cast<Caine>(a)) {
            poplinit += caine->actiuneSpeciala();
        }
    }
    popularitate = poplinit + 2*victorii;
}

std::string Jucator::avantajPopular(const std::vector<std::shared_ptr<Animal>>& inventar) const {
    std::string cmPop = inventar[0]->getAvantaj();
    int maxPart = inventar[0]->getParticipari();
    for (const auto &i : inventar) {
        int part = i->getParticipari();
        if (part > maxPart) {
            maxPart = part;
            cmPop = i->getAvantaj();
        }
    }
    return cmPop;
}

int Jucator::getPop() const {
    return popularitate;
}