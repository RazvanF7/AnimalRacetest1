//
// Created by razvan on 5/23/25.
//

#include "../include/Meniu.h"

#include <iostream>
#include "../include/Magazin.h"
#include "../include/Cal.h"
#include "../include/Exceptii.h"
void Meniu::ruleaza() {
    bool iesire = false;
    while (!iesire) {
        afisOptiuni();
        int opt;
        std::cin >> opt;
        switch (opt) {
            case 1: comandaAdaugaMagazin(); break;
            case 2: comandaAfisMagazin();  break;
            case 3: comandaCumpara();      break;
            case 4: comandaAfisJucator();  break;
            case 5: comandaAntreneaza();   break;
            case 0: iesire = true;         break;
            default:
                std::cout << "alege alta optiune\n";
        }
        if (!iesire) {
            std::cin.get();
        }
    }
}

void Meniu::afisOptiuni() {
    std::cout << "1. adauga animal in magazin\n"
              << "2. afiseaza magazin\n"
              << "3. cumpara un animal\n"
              << "4. inventar jucator\n"
              << "5) antreneaza animal\n"
              << "0) stop\n"
              << "alege optiunea: "<<std::endl;
}

void Meniu::comandaAdaugaMagazin() {
    auto& shop = Magazin::instanta();
    shop.adaugaAnimal(std::make_shared<Cal>(false,"Sigma", 5,"viteza", 1, 80, 90, "Epic"));
    std::cout << "animal adaugat in magazin\n";
}

void Meniu::comandaAfisMagazin() {
    Magazin::instanta().afisInventar();
}

void Meniu::comandaCumpara() {
    int id;
    std::cout << " alege id ul animalului pe care vrei sa il cumperi ";
    std::cin >> id;
    std::shared_ptr<Animal> animal;
    try {
            animal = Magazin::instanta().cumparaAnimal(id, player);
    }
    catch (const BaniInsuficienti& e) {
        std::cout << "eroare: " << e.what() << "\n";
    }

    if (!animal) {
        std::cout << "nu exista animalul\n";
    }
    else {
        player.adaugaAnimal(animal);
        std::cout << "animal adaugat in inventar\n";
        player-=animal->calcPret();
    }

    //TODO de verificat si corectat exceptii,
}

void Meniu::comandaAfisJucator() const {
    player.afisInventar();
    std::cout<<"\n";
    std::cout <<"bani: "<<player.getBani()<<std::endl;
}

void Meniu::comandaAntreneaza() const {
    int id;
    std::cout << " alege id ul animalului ";
    std::cin >> id;
    for (auto& a : player.getAnimale()) {
        if (a->getId() == id) {
            try {
                a->antreneaza();
                std::cout << "antrenament efectuat\n";
            } catch (const std::exception& e) {
                std::cout << "eroare antrenamenrt: " << e.what() << "\n";
            }
            return;
        }
    }
    std::cout << "nu exista animal cu id: " << id << " in grajd.\n";
}
