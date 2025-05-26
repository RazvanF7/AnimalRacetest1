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
    #include <iostream>
    template<typename A>
    class Oponent {
    protected:

        std::string nume;
        std::vector<std::shared_ptr<A>> animale{};
        int victorii;
        std::shared_ptr<StrategieSelect<A>>strat;

    public:
        Oponent(std::string nume,std::vector<std::shared_ptr<A>> anims,std::shared_ptr<StrategieSelect<A>> strat);

        virtual ~Oponent() = default;


        void pregatire() {
            for (auto &a : animale) {
                a->antrenamentANTR();
            }
        }
        friend std::ostream& operator<<(std::ostream& os, const Oponent<A>& t) {
            os << "Nume: " << t.nume << "\n";
            os << "Victorii: " << t.victorii << "\n";
            os << "Animale:\n";
            for (const auto& a : t.animale) {
                os << *a << "\n";
            }
            return os;
        }
        std::shared_ptr<A> alegePentru(Jucator& jucator) {
            return strat->alege(this->animale, jucator);
        }

        void setStrategie(std::shared_ptr<StrategieSelect<A>> stratNou) {
            strat = std::move(stratNou);
        }

        const std::vector<std::shared_ptr<A>>& getAnimale() const {
            return animale;
        }

        Oponent& operator++() {
            ++victorii;
            return *this;

        }
    };



    template<typename A>

    Oponent<A>::Oponent(std::string nume, std::vector<std::shared_ptr<A>> anims,
        std::shared_ptr<StrategieSelect<A>> strat): nume(std::move(nume)),
                        animale(std::move(anims)),victorii(0),
                        strat(std::move(strat))
    {}

    #endif //OPONENT_H
