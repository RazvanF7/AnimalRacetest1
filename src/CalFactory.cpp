//
// Created by razvan on 5/23/25.
//

#include "../include/CalFactory.h"
#include <memory>
#include "../include/Cal.h"

std::shared_ptr<Animal> CalFactory::createCalStart() {
    return std::make_shared<Cal>(false,"cal_start","viteza",1,100,30,"Normal");

}

std::shared_ptr<Animal> CalFactory::createCalMid() {
    return std::make_shared<Cal>(false,"cal_midgame","agilitate",3,200,45,"Epic");

}

std::shared_ptr<Animal> CalFactory::createCalEnd() {
    return std::make_shared<Cal>(true,"cal_endgame","control",5,300,65,"Legendar");

}

