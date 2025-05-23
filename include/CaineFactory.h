//
// Created by razvan on 5/23/25.
//

#ifndef CAINEFACTORY_H
#define CAINEFACTORY_H

#include <memory>
#include "Animal.h"

class CaineFactory {
public:
    static std::shared_ptr<Animal> createCaineStart(const std::string &nume, int participari, const std::string &av,
        int nivel, int agilitate,int loialitate, const std::string &rasa);
    static std::shared_ptr<Animal> createCaineMid(const std::string &nume, int participari, const std::string &av,
    int nivel, int agilitate,int loialitate, const std::string &rasa);
    static std::shared_ptr<Animal> createCaineEnd(const std::string &nume, int participari, const std::string &av,
    int nivel, int agilitate,int loialitate, const std::string &rasa);

};

#endif //CAINEFACTORY_H
