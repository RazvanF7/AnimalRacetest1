//
// Created by razvan on 5/23/25.
//

#include "../include/Magazin.h"
#include <iostream>
#include <algorithm>
#include "../include/Exceptii.h"

Magazin &Magazin::instanta() {
    static Magazin instance;
    return instance;
}
void Magazin::adaugaAnimal(std::shared_ptr<Animal> animal) {
    inventar.push_back(std::move(animal));
}

void Magazin::afisInventar() const {
    std::cout<<"inventar Magazin:"<<std::endl;
    for (const auto& a: inventar) {
        std::cout<<*a<<std::endl;
    }
}

std::shared_ptr<Animal> Magazin::cumparaAnimal(int id, const Jucator &cumparator) {
    const auto x = std::find_if(inventar.begin(),inventar.end(),
        [id](const std::shared_ptr<Animal>& a) {
        return a->getId() == id;
    }
    );
    if (x==inventar.end()) {
        return nullptr;
    }
    else
    {
        int pretcrt = (*x)->calcPret();
        if (cumparator.getBani()<pretcrt)
            throw BaniInsuficienti();
        auto vandut = *x;
        inventar.erase(x);
        return vandut;
    }

}
