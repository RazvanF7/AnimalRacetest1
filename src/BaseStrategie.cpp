//
// Created by razvan on 5/23/25.
//

#include "../include/BaseStrategie.h"

std::shared_ptr<Animal> BaseStrategie::alege(const std::vector<std::shared_ptr<Animal>> &anims,
    const std::string &avantaj) const {
    (void) avantaj;
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