//
// Created by razvan on 5/23/25.
//

#ifndef JUCATOR_H
#define JUCATOR_H


#include <string>
#include <vector>
#include <memory>
#include "StrategieSelect.h"
#include "Animal.h"


class Jucator{
    const int id;
    static int cont;
    std::string nume;
    std::vector<std::shared_ptr<Animal>> inventarp{};
    int bani;
    int victorii;
    int popularitate;
    std::shared_ptr<StrategieSelect> strat;

public:
    Jucator();
    Jucator(std::string nume, const std::vector <std::shared_ptr<Animal>>& invent,const std::shared_ptr<StrategieSelect> &strat);

    void adaugaAnimal(const std::shared_ptr<Animal>& animal);
    void afisInventar() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Animal>>& getAnimale() const;
    [[nodiscard]] int getBani()const;
    Jucator& operator-=(int suma);
    Jucator& operator+=(int suma);
    Jucator& operator++();
    void calcPop();
    [[nodiscard]] static std::string avantajPopular(const std::vector<std::shared_ptr<Animal>>& inventar);
    [[nodiscard]] int getPop()const;

    void pregatire() const;

    //[[nodiscard]] std::shared_ptr<Animal> alegePentru(const std::string &avantaj) const;

    void setStrategie(const std::shared_ptr<StrategieSelect> &stratNou);

    friend std::istream& operator>>(std::istream& is, Jucator& jucator);

    friend std::ostream& operator<<(std::ostream& os, const Jucator& jucator);
    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] int getId() const;
    [[nodiscard]] std::shared_ptr<StrategieSelect> getStrategie() const;
};


#endif //JUCATOR_H
