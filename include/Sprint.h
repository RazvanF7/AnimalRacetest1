//
// Created by razvan on 5/23/25.
//

#ifndef SPRINT_H
#define SPRINT_H

#include "Competitie.h"

template<typename A>
class Sprint: public Competitie<A> {
    int distanta;
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
        int abilA1 = anim1->getSprint();
        int abilA2 = anim2->getSprint();
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
    Sprint(const std::string &nume,std::vector<std::shared_ptr<A>> part, const std::string &tara, const int distanta): Competitie<A>(nume, part, tara),
    distanta(distanta) {}

    int getExtraRewards(const std::shared_ptr<A> &anim) const override{
        if (distanta/anim->getSprint()>distanta/40)
            return 300;
        return 0;
    }

};

#endif //SPRINT_H
