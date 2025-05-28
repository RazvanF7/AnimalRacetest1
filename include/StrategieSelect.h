//
// Created by razvan on 5/23/25.
//

#ifndef STRATEGIESELECT_H
#define STRATEGIESELECT_H


#include <map>
#include <memory>
#include <vector>
#include "Animal.h"


class StrategieSelect {
public:
    virtual ~StrategieSelect() = default;
    virtual std::shared_ptr<Animal> alege(const std::vector<std::shared_ptr<Animal>> &anims,
        const std::string &avantaj) const = 0;

};



#endif //STRATEGIESELECT_H
