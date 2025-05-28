//
// Created by razvan on 5/23/25.
//

#ifndef MENIU_H
#define MENIU_H


#include "Jucator.h"
#include "Competitie.h"

class Meniu {

    Jucator jucatorOm;
    std::vector<std::shared_ptr<Jucator>> oponenti;
    int zi = 1;
    std::vector<std::shared_ptr<Competitie<Animal>>> competitii;
    void initOponenti();
    bool iesire = false;
    void stop();
    [[nodiscard]] bool getIesire()const;
    static void afisOptiuni() ;
    static void comandaAfisMagazin() ;
    void comandaCumpara();
    void comandaAfisJucator() const;
    void comandaAntreneaza();
    void comandaOdihna() const;
    void comandaAfisOponenti() const;
    void initCompetitii();
    void verificaCompetitii();
public:
    void ruleaza();


};


#endif //MENIU_H
