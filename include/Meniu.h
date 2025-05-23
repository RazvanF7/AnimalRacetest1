//
// Created by razvan on 5/23/25.
//

#ifndef MENIU_H
#define MENIU_H


#include "Jucator.h"

class Meniu {
    Jucator player{"Andrei", {}};
public:
    void ruleaza();
private:
    static void afisOptiuni() ;
    static void comandaAdaugaMagazin();
    static void comandaAfisMagazin() ;
    void comandaCumpara();
    void comandaAfisJucator() const;
    void comandaAntreneaza() const;
};


#endif //MENIU_H
