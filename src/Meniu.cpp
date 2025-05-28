//
// Created by razvan on 5/23/25.
//

#include "../include/Meniu.h"

#include <iostream>
#include <Animal.h>
#include <Cal.h>
#include <Caine.h>

#include "BaseStrategie.h"
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
    std::cout<<"Care este numele tau? \n";
    std::cin>>jucatorOm;
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

    const std::shared_ptr<Animal> caine1 = std::make_shared<Caine>("Micah", "viteza",1, 90,100,"Ogar");
    const std::shared_ptr<Animal> caine2 = std::make_shared<Caine>("Stinky", "control",2,90,110,"Dalmatian");

    const std::shared_ptr<Animal> cal1   = std::make_shared<Cal>(false,"Arthur Morgan","control",1,100,45,"Normal");
    const std::shared_ptr<Animal> cal2   = std::make_shared<Cal>(true,"Nicusor","viteza",2,80,55,"Epic");

    std::vector invOp1 {caine1,cal1};
    std::vector invOp2  {caine2,cal2};

    std::shared_ptr<StrategieSelect> strat1 = std::make_shared<BaseStrategie>();
    std::shared_ptr<StrategieSelect> strat2 = std::make_shared<BaseStrategie>();

    oponenti.push_back(std::make_shared<Jucator>("Hosea",invOp1,strat1));
    oponenti.push_back(std::make_shared<Jucator>("Dutch",invOp2,strat2));
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
            animal = Magazin::instanta().cumparaAnimal(id, jucatorOm);
    }
    catch (const BaniInsuficienti& e) {
        std::cout << "eroare: " << e.what() << "\n";
    }

    if (!animal) {
        std::cout << "nu exista animalul\n";
    }
    else {
        jucatorOm.adaugaAnimal(animal);
        std::cout << "animal adaugat in inventar\n";
        jucatorOm-=animal->calcPret();
    }

    //TODO de verificat si corectat exceptii,
}

void Meniu::comandaAfisJucator() const {
    jucatorOm.afisInventar();
    std::cout<<"\n";
    std::cout <<"bani: "<<jucatorOm.getBani()<<std::endl;
}

void Meniu::comandaAntreneaza(){
    int id;
    std::cout << " alege id ul animalului ";
    std::cin >> id;
    for (const auto& a : jucatorOm.getAnimale()) {
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

    for (const auto& a : jucatorOm.getAnimale()) {
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
    std::vector<std::shared_ptr<Animal>> allowed;
    std::shared_ptr<Competitie<Animal>> competitie;
    bool esteCompCaini = false;
    while (true) {
        allowed.clear();
        std::cout << "\n competitii disponibile (ziua " << zi << ") \n";
        for (size_t i = 0; i < competitii.size(); ++i) {
            std::cout << i + 1 << ". " << competitii[i]->getNumeComp() << "\n";
        }

        int alegereComp;
        std::cout << "alege competitia dorita (1-" << competitii.size() << "): ";
        std::cin >> alegereComp;

        if (alegereComp < 1 || alegereComp > static_cast<int>(competitii.size())) {
            std::cout << "alegere invalida.\n";
            continue;
        }

        competitie = competitii[alegereComp - 1];
        esteCompCaini = (competitie->getNumeComp().find("Caini") != std::string::npos);

        for (const auto& a : jucatorOm.getAnimale()) {
            if (esteCompCaini && dynamic_cast<Caine*>(a.get())) {
                allowed.push_back(a);
            } else if (!esteCompCaini && dynamic_cast<Cal*>(a.get())) {
                allowed.push_back(a);
            }
        }

        if (allowed.empty()) {
            std::cout << "nu ai niciun animal pentru aceasta competitie.\n";
            continue;
        }

        std::cout << "animalele tale pt " << competitie->getNumeComp() << ":\n";
        for (const auto& a : allowed) {
            std::cout << "  id " << a->getId() << " " << *a;
        }
        break;
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

    jucatorOm.calcPop();

    int maxPop = jucatorOm.getPop();
    auto avpop = Jucator::avantajPopular(jucatorOm.getAnimale());
    auto tinta = jucatorOm.getId();


    for (const auto& op : oponenti) {
        op->calcPop();
        if (op->getPop() > 20 && op->getPop() > maxPop) {
            maxPop = op->getPop();
            avpop = op->avantajPopular(op->getAnimale());
            tinta = op->getId();
        }
    }

    for (const auto& op : oponenti) {
        if (op->getId() != tinta && op->getPop() > 20) {
            std::cout << op->getNume() << " isi schimba strategia catre contra ";
            op->setStrategie(std::make_shared<StrategieCounter>());
        }
    }

    std::vector<std::shared_ptr<Animal>> participanti;
    participanti.push_back(ales);

    for (const auto& op : oponenti) {
        std::vector<std::shared_ptr<Animal>> cand;
        for (auto& a : op->getAnimale()) {
            if (esteCompCaini) {
                if (dynamic_cast<Caine*>(a.get())) {
                    cand.push_back(a);
                }
            }
            else {
                if (dynamic_cast<Cal*>(a.get())) {
                    cand.push_back(a);
                }
            }
        }
        if (cand.empty())
            continue;

        auto aOp = op->getStrategie()->alege(cand, avpop);
        participanti.push_back(aOp);
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

        Jucator* propr = nullptr;
        for (const auto& ap : jucatorOm.getAnimale()) {
            if (ap->getId() == a->getId()) {
                propr = &jucatorOm;
                break;
            }
        }
        if (!propr) {
            for (const auto& op : oponenti) {
                for (auto& ao : op->getAnimale()) {
                    if (ao->getId() == a->getId()) {
                        propr = op.get();
                        break;
                    }
                }
                if (propr) break;
            }
        }
        
        std::cout << loc << ". " << a->getNume()
                  << " id: " << a->getId() << "\n";

        if (loc == 1 && propr) {
            ++(*propr);
        }

        if (propr) {
            *propr += recompensa;
            std::cout 
              << propr->getNume()<< " a primit " << recompensa << " bani pentru locul "<< loc <<std::endl;
        }

        const int extra = compNou->getExtraRewards(a);
        if (propr) {
            *propr += extra;
            std::cout << propr->getNume() << " a primit bonus extra: " << extra << std::endl;
        }
        
        recompensa = std::max(0, recompensa - 150);
        ++loc;
    }

    std::cout << "\n competitia s a incheiat\n";
}
