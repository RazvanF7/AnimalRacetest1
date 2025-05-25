//
// Created by razvan on 5/23/25.
//

#include "../include/Animal.h"
#include "../include/Exceptii.h"
#include <iostream>
int Animal::nextId = 0;
Animal::Animal():id(++nextId), nume("unknown"), avantaj("unknown"),
                    initPerf(100), pret(0), nivel(1),
                  participari(0), energie(100) {
}

Animal::Animal(std::string nume,std::string av, int nivel) :
id(++nextId),nume(std::move(nume)), avantaj(std::move(av)), initPerf(100),
pret(0), nivel(nivel), participari(0), energie(100) {
}


Animal &Animal::operator=(const Animal &other) {
    if (this != &other) {
        nume = other.nume;
        participari = other.participari;
        avantaj = other.avantaj;
        initPerf = other.initPerf;
        nivel = other.nivel;
        energie = other.energie;
        pret = other.pret;

    }
    return *this;
}

Animal &Animal::operator++(int) {
    participari++;
    return *this;
}
int Animal::extraPret() const {
    return 0;
}

int Animal::calcPret() const {
    int i = 0;
    int pretTotal = 0;
    pretTotal += extraPret();
    for ([[maybe_unused]] const auto &av : avantaj) {
        i++;
    }
    pretTotal += i*100+ nivel*100;
    return pretTotal;
}

std::ostream& operator<<(std::ostream& os, const Animal& animal) {
    os<<"nume: "<<animal.nume<<std::endl
    <<"participari: "<<animal.participari<<std::endl
    <<"pret: "<<animal.calcPret()<<std::endl
    <<"energie: "<<animal.energie<<std::endl
    <<"nivel: "<<animal.nivel<<std::endl
    <<"avantaj: "<<animal.avantaj<<std::endl;
    os<<"id: "<<animal.id<<std::endl;
    animal.afis(os);
    return os;
}

std::istream& operator>>(std::istream& is, Animal& animal) {
    is>>animal.nume;
    return is;
}


Animal &Animal::operator++() {
        ++nivel;
        return *this;
    }

bool operator<(const Animal& a, const Animal& b) {
    return a.calcPret() < b.calcPret();
}
bool operator==(const Animal& a, const Animal& b) {
    return a.calcPret() == b.calcPret();
}
void Animal::odihna() {
    if (energie>80) {
        throw EnergieMulta();
    }
    energie+=20;
    std::cout<<"Animalul s-a odihnit. Energie actuala: "<<energie<<std::endl;
}


int Animal::getId() const {
    return id;
}

int Animal::getInitPerf() const {
    return initPerf;
}

int Animal::calculeazaPerf() {
    int perf = initPerf;
    perf += extraPerf();
    perf += nivel*100;
    return perf;
}

int Animal::extraPerf() const{
    return 0;
}

std::string Animal::getAvantaj() const {
    return avantaj;
}

int Animal::getParticipari() const {
    return participari;
}
std::string Animal::getNume() const {
    return nume;
}

void Animal::crestePart() {
    participari++;
}
