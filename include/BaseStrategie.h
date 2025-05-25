//
// Created by razvan on 5/23/25.
//

#ifndef BASESTRATEGIE_H
#define BASESTRATEGIE_H

#include "StrategieSelect.h"



template<typename A>
class BaseStrategie: public StrategieSelect<A> {
public:
    std::shared_ptr<A> alege(std::vector<std::shared_ptr<A>> &anims,Jucator &juc) const override;
};

template<typename A>
std::shared_ptr<A> BaseStrategie<A>::alege(std::vector<std::shared_ptr<A>> &anims,Jucator &juc) const {
    auto best = anims.front();
    int bestscor = best->calculeazaPerf();
    for (const auto &a: anims) {
        int scor = a->calculeazaPerf();
        if (scor>bestscor) {
            best = a;
            bestscor = scor;
        }
    }
    return best;
}


#endif //BASESTRATEGIE_H
