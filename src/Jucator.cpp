//
// Created by razvan on 5/23/25.
//

#include "../include/Jucator.h"
#include "../include/Caine.h"
#include "../include/Cal.h"
#include "../include/Exceptii.h"
#include <iostream>
int Jucator::cont = 0;
Jucator::Jucator():id(++cont),nume("Normal"),inventarp({}),bani(2000),victorii(0),popularitate(0){}
Jucator::Jucator(std::string nume, const std::vector<std::shared_ptr<Animal>>& invent, const std::shared_ptr<StrategieSelect> &strat):
id(++cont),nume(std::move(nume)),bani(2000),victorii(0),popularitate(0),strat(strat) {
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
    popularitate += poplinit + 2*victorii;
}

std::string Jucator::avantajPopular(const std::vector<std::shared_ptr<Animal>>& inventar) {
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

void Jucator::pregatire() const {
    for (const auto &a : inventarp) {
        a->antrenamentANTR();
    }
}

std::shared_ptr<Animal> Jucator::alegePentru(const std::string &avantaj) const {
    return strat->alege(this->inventarp, avantaj);
}

void Jucator::setStrategie(const std::shared_ptr<StrategieSelect>& stratNou) {
    strat = stratNou;
}

std::istream& operator>>(std::istream& is, Jucator& jucator) {
    is >> jucator.nume;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Jucator& jucator) {
    os << "nume: " << jucator.nume << std::endl<<
        "bani: "<<jucator.bani<<std::endl<<
            "animale: "<<std::endl;
    for (const auto& a: jucator.inventarp) {
        std::cout<<*a<<std::endl;
    }
    os<<"victorii: "<<jucator.victorii<<std::endl<<
        "popularitate: "<<jucator.popularitate <<std::endl;
    return os;
}

std::string Jucator::getNume() const{
    return nume;
}

int Jucator::getId() const {
    return id;
}

std::shared_ptr<StrategieSelect> Jucator::getStrategie() const {
    return strat;
}
