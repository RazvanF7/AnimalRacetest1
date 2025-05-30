//
// Created by razvan on 5/23/25.
//

#include "../include/Caine.h"
#include "../include/Exceptii.h"
#include <iostream>

const std::set<std::string> Caine::rase = {"Husky", "Ogar", "Dalmatian"};
bool Caine::eRasaValida(const std::string &rasa) {
    return rase.find(rasa) != rase.end();
}
Caine::Caine(const std::string &nume, const std::string &av,
    int nivel, int loialitate, int agilitate, const std::string &rasa):
Animal(nume, av, nivel),loialitate(loialitate),agilitate(agilitate),rasa(rasa)
{
    if (!eRasaValida(rasa)) {
        throw RasaInvalida();
    }

}

void Caine::antreneaza() {
    if (energie<20) {
        throw EnergiePutina();
    }

    energie-=20;
    loialitate+=20;
    agilitate+=20;
    std::cout<<"Antrenament finalizat. Energie ramasa: "<<energie<<std::endl;
}
void Caine::odihna() {
    if (energie>80) {
        throw EnergieMulta();
    }
    energie+=20;
    std::cout<<"Cainele s-a odihnit. Energie actuala: "<<energie<<std::endl;
}
void Caine::afis(std::ostream& os) const {
    os<<"loialitate: "<<loialitate<<std::endl;
    os<<"agilitate: "<<agilitate<<std::endl;


}

int Caine::extraPret() const {
    int pretloc = 0;
    if (rasa == "Husky")
        pretloc += 300;
    else if (rasa == "Ogar")
        pretloc += 700;
    else
        pretloc += 200;
    pretloc += loialitate/2;
    pretloc += agilitate/2;
    if (participari > 6)
        pretloc -= 400;
    return pretloc;
}
int Caine::extraPerf() const {
    int perf = 0;
    if (rasa == "Husky")
        perf += 300;
    else if (rasa == "Ogar")
        perf += 700;
    else
        perf += 200;
    perf += loialitate/2;
    perf += agilitate/2;
    if (participari > 6)
        perf -= 300;
    return perf;
}


std::shared_ptr<Animal> Caine::clone() const {
    return std::make_shared<Caine>(*this);
}

void Caine::antrenamentANTR() {
    agilitate+=55;
    loialitate+=55;
    nivel++;
}

int Caine::actiuneSpeciala() {
    int extraPop = 0;
    if (loialitate>=100 && loialitate<200) {
        extraPop+=2;
    }
    else if (loialitate>=200) {
        extraPop+=4;
    }
    return extraPop;
}

int Caine::getObstacole() const {
    return loialitate;
}

int Caine::getSprint() const {
    return agilitate;
}

int Caine::costLevelUp() {
    return 100*nivel + loialitate*2 + agilitate*2;
}



