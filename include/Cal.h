//
// Created by razvan on 5/23/25.
//

#ifndef CAL_H
#define CAL_H
#include <memory>
#include <set>
#include "Animal.h"

class Cal: public Animal {
    bool copiteCustom;
    int anduranta;
    int viteza;
    std::string raritate;
    static const std::set<std::string> raritati;
protected:
    void afis(std::ostream& os) const override;
    [[nodiscard]] int extraPret() const override;
    [[nodiscard]] int extraPerf() const override;

public:
    Cal(bool copiteCustom,const std::string &nume, const std::string &av, int nivel, int anduranta,int viteza,const std::string &raritate);
    static bool eRaritateValida(const std::string &raritate);
    void antreneaza() override;
    void odihna()override;
    void upgradeCopite(int bani);
    [[nodiscard]] std::shared_ptr<Animal> clone() const override;
    void antrenamentANTR() override;
    int actiuneSpeciala() override;
    [[nodiscard]] int getObstacole() const override;
    [[nodiscard]] int getSprint() const override;
    int costLevelUp() override;
};




#endif //CAL_H
