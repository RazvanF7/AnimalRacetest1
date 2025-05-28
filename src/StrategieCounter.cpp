//
// Created by razvan on 5/23/25.
//

#include "../include/StrategieCounter.h"
#include "BaseStrategie.h"

std::shared_ptr<Animal> StrategieCounter:: alege(const std::vector<std::shared_ptr<Animal>> &anims,
    const std::string &avantaj) const {

    const std::string& counter = bate.at(avantaj);

    for (const auto& a: anims) {
        if (a->getAvantaj() == counter) {
            return a;
        }
    }
    return BaseStrategie {}.alege(anims, avantaj);

}
