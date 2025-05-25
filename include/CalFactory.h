//
// Created by razvan on 5/23/25.
//

#ifndef CALFACTORY_H
#define CALFACTORY_H
#include <memory>
#include "Animal.h"

class CalFactory {
public:
    static std::shared_ptr<Animal> createCalStart();
    static std::shared_ptr<Animal> createCalMid();
    static std::shared_ptr<Animal> createCalEnd();

};


#endif //CALFACTORY_H
