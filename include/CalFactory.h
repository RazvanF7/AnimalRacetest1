//
// Created by razvan on 5/23/25.
//

#ifndef CALFACTORY_H
#define CALFACTORY_H
#include <memory>
#include "Animal.h"

class CalFactory {
public:
    static std::shared_ptr<Animal> createCalStart(const std::string &nume, int participari, const std::string &av,
        int nivel, int anduranta,int viteza, const std::string &raritate);
    static std::shared_ptr<Animal> createCalMid(const std::string &nume, int participari, const std::string &av,
    int nivel, int anduranta,int viteza, const std::string &raritate);
    static std::shared_ptr<Animal> createCalEnd(const std::string &nume, int participari, const std::string &av,
    int nivel, int anduranta,int viteza, const std::string &raritate);

};


#endif //CALFACTORY_H
