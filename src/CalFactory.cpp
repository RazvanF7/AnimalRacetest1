//
// Created by razvan on 5/23/25.
//

#include "../include/CalFactory.h"
#include <memory>
#include "../include/Cal.h"

std::shared_ptr<Animal> CalFactory::createCalStart(const std::string &nume,
    int participari,const std::string &av, int nivel, int anduranta,
    int viteza, const std::string &raritate) {
    return std::make_shared<Cal>(false,nume,1,"viteza",1,100,30,"Normal");

}

std::shared_ptr<Animal> CalFactory::createCalMid(const std::string &nume,
    int participari,const std::string &av, int nivel, int anduranta,
    int viteza, const std::string &raritate) {
    return std::make_shared<Cal>(false,nume,1,"agilitate",3,200,45,"Epic");

}

std::shared_ptr<Animal> CalFactory::createCalEnd(const std::string &nume,
    int participari,const std::string &av, int nivel, int anduranta,
    int viteza, const std::string &raritate) {
    return std::make_shared<Cal>(true,nume,1,"control",5,300,65,"Legendar");

}

