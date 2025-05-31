//
// Created by razvan on 5/23/25.
//

#include "../include/Cal.h"
#include "../include/Exceptii.h"
#include <iostream>

const std::set<std::string> Cal::raritati = {"Normal", "Epic", "Legendar"};
bool Cal::eRaritateValida(const std::string &raritate) {
    return raritati.find(raritate) != raritati.end();
}
Cal::Cal(bool copiteCustom, const std::string &nume, const std::string &av,
    int nivel,int anduranta,int viteza, const std::string &raritate):
Animal(nume, av, nivel),
copiteCustom(copiteCustom),anduranta(anduranta),viteza(viteza),raritate(raritate)
{
    if (!eRaritateValida(raritate)) {
        throw RaritateInvalida();
    }

}
void Cal::upgradeCopite(const int bani) {
    if (bani>=500)
        copiteCustom = true;
    else throw BaniInsuficienti();
}
void Cal::antreneaza() {
    if (energie<20) {
        throw EnergiePutina();
    }

    energie-=20;
    viteza+=2;
    anduranta+=20;
    std::cout<<"Antrenament finalizat. Energie ramasa: "<<energie<<std::endl;
}

void Cal::odihna() {
    if (energie>80) {
        throw EnergieMulta();

    }
    energie+=20;
    std::cout<<"Calul s-a odihnit. Energie actuala: "<<energie<<std::endl;
}
void Cal::afis(std::ostream& os) const {
    os<<"copite speciale: ";
    if(copiteCustom) {
        os<<"da "<<std::endl;
    }
    else {
        os<<"nu "<<std::endl;
    }
    os<<"anduranta: "<<anduranta<<std::endl;
    os<<"viteza: "<<viteza<<std::endl;

}

int Cal::extraPret() const {
    int pretloc = 0;
    if (raritate == "Epic")
        pretloc += 300;
    else if (raritate == "Legendar")
        pretloc += 700;
    else
        pretloc += 100;

    if (copiteCustom) {
        pretloc *= 2;
    }
    pretloc += anduranta/2;
    pretloc += viteza*10/3;
    if (participari > 10)
        pretloc -= 400;
    return pretloc;
}


int Cal::extraPerf() const {
    int perf = 0;
    if (raritate == "Epic")
        perf += 300;
    else if (raritate == "Legendar")
        perf += 700;
    else
        perf += 100;

    if (copiteCustom) {
        perf *= 2;
    }
    perf += anduranta/2;
    perf += viteza*10/3;
    if (participari > 10)
        perf -= 500;
    return perf;
}

std::shared_ptr<Animal> Cal::clone() const {
    return std::make_shared<Cal>(*this);
}


void Cal::antrenamentANTR() {
    anduranta+=2;
    viteza+=2;
    nivel++;
}

int Cal::actiuneSpeciala() {
    int banispec = 0;
    if (energie<10) {
        throw EnergiePutina();
    }
    else {
        banispec = (anduranta+viteza)/2;
        if (copiteCustom) {
            banispec *= 2;
        }
        energie-=10;
    }
    return banispec;
}

int Cal::getObstacole() const {
    return anduranta;
}

int Cal::getSprint() const {
    return viteza;
}

int Cal::costLevelUp() {
    if (copiteCustom) {
        return 120*nivel + viteza + anduranta + 300;
    }
    return 120*nivel + viteza + anduranta;

}
