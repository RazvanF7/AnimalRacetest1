//
// Created by razvan on 5/23/25.
//

#ifndef OPONENT_H
#define OPONENT_H
#include <string>
#include <vector>
#include <memory>
#include "StrategieSelect.h"
#include "Jucator.h"

template<typename A>
class Oponent {
protected:

    std::string nume;
    int experienta;
    std::vector<std::shared_ptr<A>> animale{};
    std::string taraPreferata;
    int victorii;
    virtual void afis(std::ostream& os) const = 0;
    std::shared_ptr<StrategieSelect<A>>strat;

public:
    Oponent(std::string nume,int experienta,std::vector<std::shared_ptr<A>> anims,std::string tara,std::shared_ptr<StrategieSelect<A>> strat);

    virtual ~Oponent() = default;


    virtual void pregatire() {
        for (auto &a : animale) {
            a->antrenamentANTR();
        }
    }

    Oponent& operator++() {
        ++experienta;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os,const Oponent<A>& t)
    {
        t.afis(os);
        os << "nume: " << t.nume << std::endl
           << "ani experienta: " << t.experienta << std::endl;
        return os;
    }
    [[nodiscard]] int getExp() const;
    [[nodiscard]] int getVict() const;
    std::shared_ptr<A> alegePentru(const Jucator& jucator) {
        return strat->alege(this->animale, jucator);
    }

    void setStrategie(std::unique_ptr<StrategieSelect<A>> stratNou) {
        strat = std::move(stratNou);
    }


};

template<typename A>
int Oponent<A>::getExp() const {
    return experienta;
}
template<typename A>
int Oponent<A>::getVict() const {
    return victorii;
}


template<typename A>

Oponent<A>::Oponent(std::string nume, int experienta, std::vector<std::shared_ptr<A>> anims,
                    std::string tara, std::shared_ptr<StrategieSelect<A>> strat): nume(std::move(nume)),
                    experienta(experienta), animale(std::move(anims)), taraPreferata(std::move(tara)),victorii(0),
                    strat(std::move(strat))
{}

#endif //OPONENT_H
