//
// Created by razvan on 5/23/25.
//

#include "../include/CaineFactory.h"
#include "../include/Caine.h"

std::shared_ptr<Animal> CaineFactory::createCaineStart() {
    return std::make_shared<Caine>("caine_start","viteza",1,100,100,"Dalmatian");

}

std::shared_ptr<Animal> CaineFactory::createCaineMid() {
    return std::make_shared<Caine>("caine_midgame","agilitate",3,200,200,"Husky");

}

std::shared_ptr<Animal> CaineFactory::createCaineEnd() {
    return std::make_shared<Caine>("caine_endgame","control",5,300,300,"Ogar");

}