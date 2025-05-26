//
// Created by razvan on 5/23/25.
//

#include "../include/Meniu.h"

#include <iostream>
#include <Animal.h>
#include <Cal.h>
#include <Caine.h>

#include "BaseStrategie.h"
#include "Oponent.h"
#include "../include/CalFactory.h"
#include "../include/CaineFactory.h"
#include "../include/Magazin.h"
#include "../include/Exceptii.h"
#include "../include/Obstacole.h"
#include "../include/Sprint.h"
#include "../include/StrategieCounter.h"
void Meniu::stop() {
    iesire = true;
}
bool Meniu::getIesire() const{
    return iesire;
}

void Meniu::ruleaza() {
    auto& shop = Magazin::instanta();

    shop.adaugaAnimal(CaineFactory::createCaineStart());
    shop.adaugaAnimal(CaineFactory::createCaineMid());
    shop.adaugaAnimal(CaineFactory::createCaineEnd());

    shop.adaugaAnimal(CalFactory::createCalStart());
    shop.adaugaAnimal(CalFactory::createCalMid());
    shop.adaugaAnimal(CalFactory::createCalEnd());

    initOponenti();
    initCompetitii();


    while (!getIesire()) {
        afisOptiuni();
        int opt;
        std::cin >> opt;
        switch (opt) {
            case 1: comandaAfisMagazin();  break;
            case 2: comandaCumpara();      break;
            case 3: comandaAfisJucator();  break;
            case 4: comandaAntreneaza();   break;
            case 5: comandaOdihna();       break;
            case 6: comandaAfisOponenti(); break;
            case 0: stop();         break;
            default:
                std::cout << "alege alta optiune\n";
        }
        if (!getIesire())
            verificaCompetitii();
        if (!getIesire()) {
            std::cin.get();
        }
    }
}

void Meniu::initOponenti() {

    std::shared_ptr<Animal> caine1 = std::make_shared<Caine>("Micah", "viteza",1, 50,60,"Ogar");
    std::shared_ptr<Animal> caine2 = std::make_shared<Caine>("Stinky", "agilitate",2,60,70,"Dalmatian");

    std::shared_ptr<Animal> cal1   = std::make_shared<Cal>(false,"Arthur Morgan","control",1,55,45,"Normal");
    std::shared_ptr<Animal> cal2   = std::make_shared<Cal>(true,"Nicusor","viteza",2,65,55,"Epic");

    std::vector doarCaini{caine1,caine2};
    std::vector doarCai  {cal1,cal2};

    std::shared_ptr<StrategieSelect<Animal>> stratBase1 = std::make_shared<BaseStrategie<Animal>>();
    std::shared_ptr<StrategieSelect<Animal>> stratBase2 = std::make_shared<BaseStrategie<Animal>>();

    oponenti.push_back(std::make_shared<Oponent<Animal>>(
        "Hosea",
        std::move(doarCaini),
        stratBase1
    ));
    oponenti.push_back(std::make_shared<Oponent<Animal>>(
        "Dutch",
        std::move(doarCai),
        stratBase2
    ));
}
void Meniu::afisOptiuni() {
    std::cout
              << "1. afiseaza magazin\n"
              << "2. cumpara un animal\n"
              << "3. inventar jucator\n"
              << "4. antreneaza animal\n"
              << "5. odihna\n"
              << "6. afiseaza oponenti: \n"
              << "0. stop\n"
              << "alege optiunea: "<<std::endl;
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

void Meniu::comandaAntreneaza(){
    int id;
    std::cout << " alege id ul animalului ";
    std::cin >> id;
    for (const auto& a : player.getAnimale()) {
        if (a->getId() == id) {
            try {
                a->antreneaza();
                std::cout << "antrenament efectuat\n";
                ++zi;
            } catch (const std::exception& e) {
                std::cout << "eroare antrenamenrt: " << e.what() << "\n";
            }
            return;
        }
    }
    std::cout << "nu exista animal cu id: " << id << " in grajd.\n";
}

void Meniu::comandaOdihna() const {
    int id;
    std::cout << " alege id-ul animalului pentru odihna: ";
    std::cin >> id;

    for (const auto& a : player.getAnimale()) {
        if (a->getId() == id) {
            try {
                a->odihna();
            } catch (const std::exception& e) {
                std::cout << "Eroare la odihna: " << e.what() << "\n";
            }
            return;
        }
    }

    std::cout << "nu exista animal cu id: " << id << " in grajd.\n";
}

void Meniu::comandaAfisOponenti() const {
    if (oponenti.empty()) {
        std::cout << "nu exista oponenti de afisat.\n";
        return;
    }

    std::cout << "lista oponentilor:\n";
    for (const auto& opp : oponenti) {
        std::cout << *opp << std::endl;
    }
}
void Meniu::initCompetitii() {
    using namespace std;

    vector<shared_ptr<Animal>> v1,v2;



    competitii.push_back(make_shared<Obstacole<Animal>>("Obstacole Caini", v1, "RO", 5));
    competitii.push_back(make_shared<Obstacole<Animal>>("Obstacole Cai", v2, "RO", 5));
    competitii.push_back(make_shared<Sprint<Animal>>("Sprint Caini", v1, "RO", 100));
    competitii.push_back(make_shared<Sprint<Animal>>("Sprint Cai", v2, "RO", 100));
}


void Meniu::verificaCompetitii() {
    if (zi % 5 != 0) return;

    std::cout << "\n competitii disponibile (ziua " << zi << ") \n";
    for (size_t i = 0; i < competitii.size(); ++i) {
        std::cout << i + 1 << ". " << competitii[i]->getNumeComp() << "\n";
    }

    int alegereComp;
    std::cout << "alege competitia dorita (1-" << competitii.size() << "): ";
    std::cin >> alegereComp;

    if (alegereComp < 1 || alegereComp > (int)competitii.size()) {
        std::cout << "alegere invalida.\n";
        return;
    }

    auto competitie = competitii[alegereComp - 1];
    bool isDogComp =
        (competitie->getNumeComp().find("Caini") != std::string::npos);


    std::vector<std::shared_ptr<Animal>> allowed;
    for (const auto& a : player.getAnimale()) {
        if (isDogComp) {

            if (dynamic_cast<Caine*>(a.get()))
                allowed.push_back(a);
        } else {

            if (dynamic_cast<Cal*>(a.get()))
                allowed.push_back(a);
        }
    }

    if (allowed.empty()) {
        std::cout << "Nu ai niciun animal pentru aceasta competitie.\n";
        return;
    }


    std::cout << "animalele tale pt "<< competitie->getNumeComp()<< "':\n";
    for (auto& a : allowed) {
        std::cout << "  id " << a->getId() <<" ";
        std::cout<<*a;
    }


    int idAnimal;
    std::cout << "alege ID-ul dintre cele de mai sus: ";
    std::cin >> idAnimal;

    std::shared_ptr<Animal> ales;
    for (const auto& a : allowed) {
        if (a->getId() == idAnimal) {
            ales = a;
            (*a)++;
            break;
        }
    }
    if (!ales) {
        std::cout << "id invalid pentru competitie\n";
        return;
    }

    player.calcPop();
    if (player.getPop() > 20) {
        std::cout << " popularitate ta a crescut: oponentii isi schimba strategia\n";
        for (const auto& opp : oponenti) {
            opp->setStrategie(std::make_shared<StrategieCounter<Animal>>());
        }
    }

    std::vector<std::shared_ptr<Animal>> participanti;
    participanti.push_back(ales);

    for (auto& opp : oponenti) {
        for (auto& a : opp->getAnimale()) {
            if ((dynamic_cast<Cal*>(ales.get()) && dynamic_cast<Cal*>(a.get())) ||
                (dynamic_cast<Caine*>(ales.get()) && dynamic_cast<Caine*>(a.get()))) {
                participanti.push_back(a);
                break;
            }
        }
    }

    if (participanti.size() < 2) {
        std::cout << "prea putini participanti\n";
        return;
    }

    std::shared_ptr<Competitie<Animal>> compNou;


    if (dynamic_cast<Sprint<Animal>*>(competitie.get())) {
        const auto* sprint = dynamic_cast<Sprint<Animal>*>(competitie.get());
        compNou = std::make_shared<Sprint<Animal>>(sprint->getNumeComp(), participanti, "RO", 100);
    } else {
        const auto* obst = dynamic_cast<Obstacole<Animal>*>(competitie.get());
        compNou = std::make_shared<Obstacole<Animal>>(obst->getNumeComp(), participanti, "RO", 5);
    }

    std::cout << "\n a inceput competitia \n";
    std::vector<std::shared_ptr<Animal>> clasament = compNou->run();
    ++zi;
    for (const auto& op: oponenti) {
        op->pregatire();
    }

    std::cout << "\n clasament final \n";

    int recompensa = 400;
    int loc = 1;

    for (const auto& a : clasament) {
        std::cout << loc << ". " << a->getNume() << " id: " << a->getId() << "\n";

        if (loc == 1) {
            bool esteJucator = false;

            for (const auto& a_player : player.getAnimale()) {
                if (a_player->getId() == a->getId()) {
                    esteJucator = true;
                    break;
                }
            }

            if (esteJucator) {
                ++player;
            } else {
                for (const auto& opp : oponenti) {
                    for (const auto& a_opp : opp->getAnimale()) {
                        if (a_opp->getId() == a->getId()) {
                            ++(*opp);
                            break;
                        }
                    }
                }
            }
        }
        for (const auto& a_player : player.getAnimale()) {
            if (a_player->getId() == a->getId()) {
                player+=recompensa;
                std::cout << " ai primit " << recompensa << " bani pentru locul " << loc << "!\n";
            }
        }

        recompensa = std::max(0, recompensa - 150);
        ++loc;
    }

    std::cout << "\n competitia s a incheiat\n";

}
