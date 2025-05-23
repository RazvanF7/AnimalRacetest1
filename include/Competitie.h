//
// Created by razvan on 5/23/25.
//

#ifndef COMPETITIE_H
#define COMPETITIE_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>


template<typename A>
class Competitie {
    std::string numeComp;
    std::vector<std::shared_ptr<A>> participanti{};
    std::string tara;

protected:
    virtual int compara(const std::shared_ptr<A> &anim1, const std::shared_ptr<A> &anim2) const = 0;
    bool bate(const std::string& atr1, const std::string& atr2) {
        if (atr1 == "viteza" && atr2 == "agilitate") return true;
        if (atr1 == "control" && atr2 == "viteza") return true;
        if (atr1 == "agilitate" && atr2 == "control") return true;
        return false;
    }

public:
    virtual ~Competitie() = default;
    Competitie(std::string nume,std::vector<std::shared_ptr<A>> part, std::string country): numeComp(std::move(nume)),
    participanti(std::move(part)),tara(std::move(country)) {

    }

    [[nodiscard]] std::vector<std::shared_ptr<A>> run() const;

    [[nodiscard]] virtual int getExtraRewards() const = 0;
};

template<typename A>
std::vector<std::shared_ptr<A>> Competitie<A>::run() const {
    int n = participanti.size();
    std::unordered_map<int, int> scor;
    scor.reserve(n);
    for (int i=0;i<n;++i) {

        for (int j=i+1;j<n;++j) {
            int rez = compara(participanti[i], participanti[j]);
            if (rez>0)
                ++scor[participanti[i]->getId()];
            else if (rez<0)
                ++scor[participanti[j]->getId()];

        }
    }
    std::sort(participanti.begin(),participanti.end(),[scor](auto &anim1, const std::shared_ptr<A> &anim2) {
        int s1 = scor[anim1->getId()];
        int s2 = scor[anim2->getId()];
        if (s1!=s2) return s1>s2;
        return anim1->getId() < anim2->getId();
    });

    return participanti;



}

#endif //COMPETITIE_H
