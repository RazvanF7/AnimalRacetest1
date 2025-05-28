//
// Created by razvan on 5/23/25.
//

#ifndef BASESTRATEGIE_H
#define BASESTRATEGIE_H

#include "StrategieSelect.h"



class BaseStrategie: public StrategieSelect{
public:
    [[nodiscard]] std::shared_ptr<Animal> alege(const std::vector<std::shared_ptr<Animal>> &anims,
    const std::string &animal) const override;
};





#endif //BASESTRATEGIE_H
