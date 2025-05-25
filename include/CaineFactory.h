//
// Created by razvan on 5/23/25.
//

#ifndef CAINEFACTORY_H
#define CAINEFACTORY_H

#include <memory>
#include "Animal.h"

class CaineFactory {
public:
    static std::shared_ptr<Animal> createCaineStart();
    static std::shared_ptr<Animal> createCaineMid();
    static std::shared_ptr<Animal> createCaineEnd();

};

#endif //CAINEFACTORY_H
