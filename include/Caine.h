//
// Created by razvan on 5/23/25.
//

#ifndef CAINE_H
#define CAINE_H
#include <set>

#include "Animal.h"


class Caine: public Animal {
    int loialitate;
    int agilitate;
    std::string rasa;
    static const std::set<std::string> rase;
protected:
    void afis(std::ostream& os) const override;
    [[nodiscard]] int extraPret() const override;
    [[nodiscard]] int extraPerf() const override;

public:
    Caine(const std::string &nume, const std::string &av, int nivel, int loialitate,int agilitate,const std::string &rasa);
    static bool eRasaValida(const std::string &rasa);
    void antreneaza() override;
    void odihna()override;
    bool operator<(const Caine& other) const;
    [[nodiscard]] std::shared_ptr<Animal> clone() const override;
    void antrenamentANTR() override;

    int actiuneSpeciala() override;

    [[nodiscard]] int getObstacole() const override;
    [[nodiscard]] int getSprint() const override;
};



#endif //CAINE_H
