//
// Created by razvan on 5/23/25.
//

#ifndef OBSTACOLE_H
#define OBSTACOLE_H


#include "Competitie.h"
#include "Cal.h"
template<typename A>
class Obstacole: public Competitie<A> {
    int nrObs;
protected:
    int compara(const std::shared_ptr<A> &anim1, const std::shared_ptr<A> &anim2) const override{

        int scorA1 = 0;
        int scorA2 = 0;
        int perfA1 = anim1->calculeazaPerf();
        int perfA2 = anim2->calculeazaPerf();
        if (perfA1>perfA2) {
            scorA1++;
        }
        else if (perfA1<perfA2) {
            scorA2++;
        }
        int abilA1 = anim1->getObstacole();
        int abilA2 = anim2->getObstacole();
        if (abilA1>abilA2) {
            scorA1++;
        }
        else if (abilA1<abilA2) {
            scorA2++;
        }

        if (this->bate(anim1->getAvantaj(),anim2->getAvantaj())) {
            scorA1+=2;
        }
        else if (this->bate(anim2->getAvantaj(),anim1->getAvantaj())) {
            scorA2+=2;
        }
        if (scorA1>scorA2) {
            return 1;
        }
        else if (scorA1<scorA2) {
            return -1;
        }
        return 0;
    }
public:
    Obstacole(std::string nume,std::vector<std::shared_ptr<A>> part, std::string tara, const int nrObs): Competitie<A>(nume, part, tara),
    nrObs(nrObs) {}

    int getExtraRewards(const std::shared_ptr<A> &anim) const override{
        int obsPerfecte = 0;
        int prag = nrObs*10;
        while (anim->getObstacole()>prag) {
            obsPerfecte++;
            prag += 50;
        }
        const int baniObs = obsPerfecte*50;
        return baniObs;
    }



};

#endif //OBSTACOLE_H
