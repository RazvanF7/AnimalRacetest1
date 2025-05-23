//
// Created by razvan on 5/23/25.
//

#ifndef STRATEGIECOUNTER_H
#define STRATEGIECOUNTER_H

#include "StrategieSelect.h"
#include "BaseStrategie.h"
#include <map>

template<typename A>
class StrategieCounter: public StrategieSelect<A> {
    const std::map<std::string, std::string> bate = {{"agilitate", "viteza"},{"viteza", "control"},
        {"control","agilitate"}};
public:
    std::shared_ptr<A> alege(std::vector<std::shared_ptr<A>> &anims,Jucator &juc) const override;

};

template<typename A>
std::shared_ptr<A> StrategieCounter<A>:: alege(std::vector<std::shared_ptr<A>> &anims, Jucator &juc) const {
    const auto jucAnimale = juc.getAnimale();
    const std::string avPop = juc.avantajPopular(jucAnimale);

    std::string counter = bate.at(avPop);

    for (const auto& a: anims) {
        if (a.getAvantaj() == counter) {
            return a;
        }
    }
    return BaseStrategie<A> {}.alege(anims, juc);

}

#endif //STRATEGIECOUNTER_H
