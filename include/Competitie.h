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
    bool bate(const std::string& atr1, const std::string& atr2) const{
        if (atr1 == "viteza" && atr2 == "agilitate") return true;
        if (atr1 == "control" && atr2 == "viteza") return true;
        if (atr1 == "agilitate" && atr2 == "control") return true;
        return false;
    }

public:
    virtual ~Competitie() = default;
    bool accepts(const std::shared_ptr<A> &a) const {
        return true;
    }
    Competitie(std::string nume,std::vector<std::shared_ptr<A>> part, std::string tara): numeComp(std::move(nume)),
    participanti(std::move(part)),tara(std::move(tara)) {

    }

    [[nodiscard]] std::vector<std::shared_ptr<A>> run() const;

    [[nodiscard]] virtual int getExtraRewards(const std::shared_ptr<A> &anim) const = 0;
    [[nodiscard]] std::string getNumeComp() const {
        return numeComp;
    };
};


template<typename A>
std::vector<std::shared_ptr<A>> Competitie<A>::run() const {
    // make a mutable copy
    std::vector<std::shared_ptr<A>> rezultate = participanti;

    int n = rezultate.size();
    std::unordered_map<int,int> scor;
    scor.reserve(n);
    for (auto &a : rezultate) {
        scor[a->getId()] = 0;
    }


    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int rez = compara(rezultate[i], rezultate[j]);
            if (rez > 0)
                ++scor[rezultate[i]->getId()];
            else if (rez < 0)
                ++scor[rezultate[j]->getId()];
        }
    }

    std::sort(
      rezultate.begin(), rezultate.end(),
      [scor](auto &anim1, auto &anim2) {
          int s1 = scor.at(anim1->getId());
          int s2 = scor.at(anim2->getId());
          if (s1 != s2) return s1 > s2;
          return anim1->getId() < anim2->getId();
      }
    );

    return rezultate;
}

#endif //COMPETITIE_H
