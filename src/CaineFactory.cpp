//
// Created by razvan on 5/23/25.
//

#include "../include/CaineFactory.h"
#include "../include/Caine.h"

std::shared_ptr<Animal> CaineFactory::createCaineStart(const std::string &nume,
    int participari,const std::string &av, int nivel, int agilitate,
    int loialitate, const std::string &rasa) {
    return std::make_shared<Caine>(nume,1,"viteza",1,100,100,"Dalmatian");

}

std::shared_ptr<Animal> CaineFactory::createCaineMid(const std::string &nume,
    int participari,const std::string &av, int nivel, int agilitate,
    int loialitate, const std::string &rasa) {
    return std::make_shared<Caine>(nume,1,"agilitate",3,200,200,"Husky");

}

std::shared_ptr<Animal> CaineFactory::createCaineEnd(const std::string &nume,
    int participari,const std::string &av, int nivel, int agilitate,
    int loialitate, const std::string &rasa) {
    return std::make_shared<Caine>(nume,1,"control",5,300,300,"Ogar");

}