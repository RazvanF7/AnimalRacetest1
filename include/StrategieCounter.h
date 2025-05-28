//
// Created by razvan on 5/23/25.
//

#ifndef STRATEGIECOUNTER_H
#define STRATEGIECOUNTER_H

#include "StrategieSelect.h"
#include "Animal.h"
#include <map>


class StrategieCounter: public StrategieSelect {
    const std::map<std::string, std::string> bate = {{"agilitate", "viteza"},{"viteza", "control"},
        {"control","agilitate"}};
public:
    [[nodiscard]] std::shared_ptr<Animal> alege(const std::vector<std::shared_ptr<Animal>> &anims,
    const std::string &avantaj) const override;

};


#endif //STRATEGIECOUNTER_H
