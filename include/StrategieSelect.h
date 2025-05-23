//
// Created by razvan on 5/23/25.
//

#ifndef STRATEGIESELECT_H
#define STRATEGIESELECT_H


#include <memory>
#include <vector>
#include "Jucator.h"

template<typename A>
class StrategieSelect {
public:
    virtual ~StrategieSelect() = default;
    virtual std::shared_ptr<A> alege(std::vector<std::shared_ptr<A>> &anims,Jucator &juc) const = 0;
};


#endif //STRATEGIESELECT_H
