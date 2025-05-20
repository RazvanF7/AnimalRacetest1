#include <iostream>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <exception>
#include <algorithm>

class RaritateInvalida: public std::exception {
    public:
        [[nodiscard]] const char* what() const noexcept override{
            return "Raritate invalida";

        }
};

class EnergiePutina: public std::exception {
    public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Energie insuficienta";
    }
};

class EnergieMulta : public std::exception {
    public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Prea multa energie";
    }
};
class RasaInvalida: public std::exception {
    public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Rasa invalida";
    }
};
class BaniInsuficienti: public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Bani insuficienti";
    }
};
class Animal {
    const int id;
    static int nextId;
    std::string nume;
    std::set<std::string> avantaj;
    int initPerf;
    int pret;
    int nivel;
protected:
    virtual void afis(std::ostream&) const{}
    [[nodiscard]] virtual int extraPret() const;
    int varsta;
    int energie;
    [[nodiscard]] int getInitPerf() const;
    [[nodiscard]] virtual int extraPerf() const;

public:
    Animal();
    Animal(std::string  nume, int varsta, const std::set<std::string> &av, int nivel);
    Animal(const Animal& other) = default;

    Animal& operator=(const Animal& other);

    virtual ~Animal() = default;

    friend std::ostream& operator<<(std::ostream& os, const Animal& animal);

    friend std::istream& operator>>(std::istream& is, Animal& animal);

    Animal& operator++(int);

    virtual void antreneaza() = 0;

    virtual void odihna();

    [[nodiscard]] virtual int calcPret() const;

    [[nodiscard]] virtual std::shared_ptr<Animal> clone() const = 0;

    Animal& operator++();
    Animal& operator+=(const std::string& adv);

    friend bool operator<(const Animal& a, const Animal& b);
    friend bool operator==(const Animal& a, const Animal& b);
    [[nodiscard]] int getId() const;
    virtual void antrenamentANTR();
    virtual int calculeazaPerf(int x, int y);
};
int Animal::nextId = 0;
Animal::Animal():id(++nextId), nume("unknown"), avantaj({"unknown"}),
                    initPerf(100), pret(0), nivel(1),
                  varsta(1), energie(100) {
}

Animal::Animal(std::string nume, int varsta, const std::set<std::string> &av, int nivel) :
id(++nextId),nume(std::move(nume)), avantaj(av), initPerf(100),
pret(0), nivel(nivel), varsta(varsta), energie(100) {
}


Animal &Animal::operator=(const Animal &other) {
    if (this != &other) {
        nume = other.nume;
        varsta = other.varsta;
        avantaj = other.avantaj;
        initPerf = other.initPerf;
        nivel = other.nivel;
        energie = other.energie;
        pret = other.pret;

    }
    return *this;
}

Animal &Animal::operator++(int) {
    varsta++;
    return *this;
}
int Animal::extraPret() const {
    return 0;
}

int Animal::calcPret() const {
    int i = 0;
    int pretTotal = 0;
    pretTotal += extraPret();
    for (auto av : avantaj) {
        i++;
    }
    pretTotal += i*100+ nivel*100;
    return pretTotal;
}

std::ostream& operator<<(std::ostream& os, const Animal& animal) {
    os<<"nume: "<<animal.nume<<std::endl
    <<"varsta: "<<animal.varsta<<std::endl
    <<"pret: "<<animal.calcPret()<<std::endl
    <<"energie: "<<animal.energie<<std::endl
    <<"nivel: "<<animal.nivel<<std::endl
    <<"avantaje: "<<" ";
    for (const auto &av : animal.avantaj) {
        os<<av<<" ";
    }
    os<<"id: "<<animal.id<<std::endl;
    animal.afis(os);
    return os;
}

std::istream& operator>>(std::istream& is, Animal& animal) {
    is>>animal.nume;
    return is;
}


Animal &Animal::operator++() {
        ++nivel;
        return *this;
    }

Animal& Animal::operator+=(const std::string& adv) {
    avantaj.insert(adv);
    return *this;
}
bool operator<(const Animal& a, const Animal& b) {
    return a.calcPret() < b.calcPret();
}
bool operator==(const Animal& a, const Animal& b) {
    return a.calcPret() == b.calcPret();
}
void Animal::odihna() {
    if (energie>80) {
        throw EnergieMulta();
    }
    energie+=20;
    std::cout<<"Animalul s-a odihnit. Energie actuala: "<<energie<<std::endl;
}


int Animal::getId() const {
    return id;
}

void Animal::antrenamentANTR() {
    nivel++;
}
int Animal::getInitPerf() const {
    return initPerf;
}

int Animal::calculeazaPerf(const int x, const int y) {
    int i = 0;
    int perf = initPerf;
    perf += extraPerf();
    for (auto av : avantaj) {
        i++;
    }
    perf += i*100 + nivel*100;
    perf += x * 2 + y*3;
    return perf;
}

int Animal::extraPerf() const{
    return 0;
}


//      Clasa Cal

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
    Cal(const std::string &nume, int varsta, const std::set<std::string> &av, int nivel, int anduranta,int viteza,const std::string &raritate);
    static bool eRaritateValida(const std::string &raritate);
    void antreneaza() override;
    void odihna()override;
    void upgradeCopite();
    [[nodiscard]] std::shared_ptr<Animal> clone() const override;
    bool operator<(const Cal& other) const;

};



const std::set<std::string> Cal::raritati = {"Normal", "Epic", "Legendar"};
bool Cal::eRaritateValida(const std::string &raritate) {
    return raritati.find(raritate) != raritati.end();
}
Cal::Cal(const std::string &nume, int varsta, const std::set<std::string> &av,
    int nivel,int anduranta,int viteza, const std::string &raritate):
Animal(nume, varsta, av, nivel),
copiteCustom(false),anduranta(anduranta),viteza(viteza),raritate(raritate)
{
    if (!eRaritateValida(raritate)) {
        throw RaritateInvalida();
    }

}
void Cal::upgradeCopite() {
    copiteCustom = true;
}
void Cal::antreneaza() {
    if (energie<20) {
        throw EnergiePutina();
    }

    energie-=20;
    viteza+=20;
    anduranta+=20;
    std::cout<<"Antrenament finalizat. Energie ramasa: "<<energie<<std::endl;
}

void Cal::odihna() {
    if (energie>80) {
        throw EnergieMulta();

    }
    energie+=20;
    std::cout<<"Calul s-a odihnit. Energie actuala: "<<energie<<std::endl;
}
void Cal::afis(std::ostream& os) const {
    os<<"Copite speciale: ";
    if(copiteCustom) {
        os<<"da "<<std::endl;
    }
    else {
        os<<"nu "<<std::endl;
    }
    os<<"anduranta: "<<anduranta<<std::endl;
    os<<"viteza: "<<viteza<<std::endl;

}

int Cal::extraPret() const {
    int pretloc = 0;
    if (raritate == "Epic")
        pretloc += 300;
    else if (raritate == "Legendar")
        pretloc += 700;
    else
        pretloc += 100;

    if (copiteCustom) {
        pretloc *= 2;
    }
    pretloc += anduranta/2;
    pretloc += viteza/3;
    if (varsta > 10)
        pretloc -= 400;
    return pretloc;
}

bool Cal::operator<(const Cal& other) const {
    return (viteza + anduranta) < (other.viteza + other.anduranta);
}

int Cal::extraPerf() const {
    int perf = 0;
    if (raritate == "Epic")
        perf += 300;
    else if (raritate == "Legendar")
        perf += 700;
    else
        perf += 100;

    if (copiteCustom) {
        perf *= 2;
    }
    perf += anduranta/2;
    perf += viteza/3;
    if (varsta > 10)
        perf -= 500;
    return perf;
}

std::shared_ptr<Animal> Cal::clone() const {
    return std::make_shared<Cal>(*this);
}

// Clasa Caine




class Caine: public Animal {
    bool sanie;
    int loialitate;
    int agilitate;
    std::string rasa;
    static const std::set<std::string> rase;
protected:
    void afis(std::ostream& os) const override;
    [[nodiscard]] int extraPret() const override;
    [[nodiscard]] int extraPerf() const override;

public:
    Caine(const std::string &nume, int varsta, const std::set<std::string> &av, int nivel, int loialitate,int agilitate,const std::string &rasa);
    static bool eRasaValida(const std::string &rasa);
    void antreneaza() override;
    void odihna()override;
    void upgradeSanie();
    bool operator<(const Caine& other) const;
    [[nodiscard]] std::shared_ptr<Animal> clone() const override;
};

const std::set<std::string> Caine::rase = {"Husky", "Ogar", "Dalmatian"};
bool Caine::eRasaValida(const std::string &rasa) {
    return rase.find(rasa) != rase.end();
}
Caine::Caine(const std::string &nume, int varsta, const std::set<std::string> &av,
    int nivel, int loialitate, int agilitate, const std::string &rasa):
Animal(nume, varsta, av, nivel),
sanie(false),loialitate(loialitate),agilitate(agilitate),rasa(rasa)
{
    if (!eRasaValida(rasa)) {
        throw RasaInvalida();
    }

}
void Caine::antreneaza() {
    if (energie<20) {
        throw EnergiePutina();
    }

    energie-=20;
    loialitate+=40;
    agilitate+=20;
    std::cout<<"Antrenament finalizat. Energie ramasa: "<<energie<<std::endl;
}
void Caine::upgradeSanie() {
    sanie=true;
}
void Caine::odihna() {
    if (energie>80) {
        throw EnergieMulta();

    }
    energie+=20;
    std::cout<<"Cainele s-a odihnit. Energie actuala: "<<energie<<std::endl;
}
void Caine::afis(std::ostream& os) const {
    os<<"Caine de sanie: ";
    if(sanie) {
        os<<"da "<<std::endl;
    }
    else {
        os<<"nu "<<std::endl;
    }
    os<<"loialitate: "<<loialitate<<std::endl;
    os<<"agilitate: "<<agilitate<<std::endl;


}

int Caine::extraPret() const {
    int pret = 0;
    if (rasa == "Husky")
        pret += 300;
    else if (rasa == "Ogar")
        pret += 700;
    else
        pret += 200;

    if (sanie) {
        pret *= 2;
    }
    pret += loialitate/2;
    pret += agilitate/2;
    if (varsta > 6)
        pret -= 400;
    return pret;
}
int Caine::extraPerf() const {
    int perf = 0;
    if (rasa == "Husky")
        perf += 300;
    else if (rasa == "Ogar")
        perf += 700;
    else
        perf += 200;

    if (sanie) {
        perf *= 2;
    }
    perf += loialitate/2;
    perf += agilitate/2;
    if (varsta > 6)
        perf -= 300;
    return perf;
}

bool Caine::operator<(const Caine& other) const{
    return (agilitate + loialitate) < (other.agilitate + other.loialitate);
}


std::shared_ptr<Animal> Caine::clone() const {
    return std::make_shared<Caine>(*this);
}

// clasa Antrenor
template<typename T>
class Antrenor {
    std::string nume;
    int experienta;
    std::string taraPreferata;

protected:
    std::vector<std::shared_ptr<T>> animale;
    virtual void afis(std::ostream&) const{}
public:

    Antrenor(std::string nume, int experienta, const std::vector<std::shared_ptr<T>> &anim, std::string taraPreferata);

    virtual ~Antrenor() = default;
    virtual void pregatire() = 0;

    template<typename A>
    friend std::ostream &operator<<(std::ostream &os, const Antrenor<A> &antrenor);

    Antrenor &operator++();

};

template<typename T>
Antrenor<T>::Antrenor(std::string nume, int experienta, const std::vector<std::shared_ptr<T>> &anim, std::string taraPreferata):
nume(std::move(nume)), experienta(experienta), taraPreferata(std::move(taraPreferata)){
    for (auto const& a : anim) {
        auto p = std::dynamic_pointer_cast<T>(a->clone());
        if (!p)
            throw std::runtime_error("fail ntrenor");
        animale.push_back(std::move(p));
    }
}
template<typename T>
std::ostream &operator<<(std::ostream &os, const Antrenor<T> &antrenor) {
    antrenor.afis(os);
    os<<"nume: "<<antrenor.nume<<std::endl<<
        "ani experienta: "<<antrenor.experienta<<std::endl;
    return os;
}

template<typename T>
Antrenor<T> &Antrenor<T>::operator++() {
    experienta++;
    return *this;
}

//clasa Calaret

class Calaret: virtual public Antrenor<Cal> {
    int greutate;
    int inaltime;
    void afis(std::ostream &os) const override;

public:
    Calaret(const std::string &nume, int experienta, const std::vector<std::shared_ptr<Cal>>& cal,const std::string &taraPreferata,int greutate,int inaltime);
    ~Calaret() override = default;

    void pregatire()override;


};
Calaret::Calaret(const std::string &nume, int experienta,
    const std::vector<std::shared_ptr<Cal>>& cal,const std::string &taraPreferata, int greutate, int inaltime):
Antrenor<Cal>(nume,experienta,cal,taraPreferata),
greutate(greutate), inaltime(inaltime) {

}
void Calaret::afis(std::ostream &os) const {
    os<<"CALARET"<<std::endl;
}

void Calaret::pregatire() {
    for (const auto& c: animale) {
        c->antrenamentANTR();
    }
}

class Dresor: virtual public Antrenor<Caine> {

    int eficientaComanda;
    void afis(std::ostream &os) const override;

public:
    Dresor(const std::string &nume, int experienta, const std::vector<std::shared_ptr<Caine>>& caini,const std::string &taraPreferata, int eficientaComanda);
    void pregatire()override;
};

Dresor::Dresor(const std::string &nume, int experienta, const std::vector<std::shared_ptr<Caine>>& caini,const std::string &taraPreferata, int eficientaComanda):
Antrenor<Caine>(nume,experienta,caini,taraPreferata), eficientaComanda(eficientaComanda) {

}

void Dresor::pregatire() {
    for (const auto& c: animale) {
        c->antrenamentANTR();
    }
}
void Dresor::afis(std::ostream &os) const {
    os<<"DRESOR"<<std::endl;
}


//diamant
class AntrenorHibrid : public Calaret, public Dresor {
public:

    AntrenorHibrid(
        const std::string& nume,int experienta,const std::string& taraPreferata,
        const std::vector<std::shared_ptr<Cal>>& cai,const std::vector<std::shared_ptr<Caine>>& caini,
        int greutate,int inaltime,int eficientaComanda): Antrenor<Cal>(nume,experienta,cai,taraPreferata),
    Antrenor<Caine>(nume,experienta,caini,taraPreferata),
    Calaret(nume,experienta,cai,taraPreferata, greutate, inaltime),
    Dresor(nume,experienta,caini,taraPreferata, eficientaComanda){

    }


protected:
    void afis(std::ostream& os) const override {
        os << "ANTRENOR HIBRID"<<std::endl;
    }

public:

    void pregatire() override {
        Calaret::pregatire();
        Dresor ::pregatire();
    }

};

//Jucator

class Jucator{
    std::string nume;
    std::vector<std::shared_ptr<Animal>> inventarp;
    int bani;
public:
    Jucator(std::string nume, const std::vector <std::shared_ptr<Animal>>& inventarp);

    void adaugaAnimal(const std::shared_ptr<Animal>& animal);
    void afisInventar() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Animal>>& getAnimale() const;
    [[nodiscard]] int getBani()const;
    Jucator& operator-=(int suma);

};

Jucator::Jucator(std::string nume, const std::vector<std::shared_ptr<Animal>>& invent):
nume(std::move(nume)),bani(2000) {
    for (auto const& i : invent) {
        inventarp.push_back(i->clone());
    }

}
Jucator& Jucator::operator-=(int suma) {
    if (bani < suma)
        throw BaniInsuficienti();
    bani -= suma;
    return *this;
}
int Jucator::getBani() const{
    return bani;
}
void Jucator::adaugaAnimal(const std::shared_ptr<Animal>& animal) {
    inventarp.push_back(animal->clone());
}

void Jucator::afisInventar() const {
    std::cout<<"animalele lui "<<nume<<std::endl;
    for (const auto& a: inventarp) {
        std::cout<<*a<<std::endl;
    }
}

const std::vector<std::shared_ptr<Animal>>& Jucator::getAnimale() const {
    return inventarp;
}


//m1agazin
class Magazin {
    Magazin() = default;
    ~Magazin() = default;
    std::vector<std::shared_ptr<Animal>> inventar;

public:
    static Magazin& instanta();
    Magazin(const Magazin&) = delete;
    Magazin& operator=(const Magazin&) = delete;

    void adaugaAnimal(std::shared_ptr<Animal> animal);
    void afisInventar() const;

    std::shared_ptr<Animal> cumparaAnimal(int id, Jucator &cumparator);

};

Magazin &Magazin::instanta() {
    static Magazin instance;
    return instance;
}
void Magazin::adaugaAnimal(std::shared_ptr<Animal> animal) {
    inventar.push_back(std::move(animal));
}

void Magazin::afisInventar() const {
    std::cout<<"inventar Magazin:"<<std::endl;
    for (const auto& a: inventar) {
        std::cout<<*a<<std::endl;
    }
}

std::shared_ptr<Animal> Magazin::cumparaAnimal(int id, Jucator &cumparator) {
    const auto x = std::find_if(inventar.begin(),inventar.end(),
        [id](const std::shared_ptr<Animal>& a) {
        return a->getId() == id;
    }
    );
    if (x==inventar.end()) {
        return nullptr;
    }
    else
        {
        int pretcrt = (*x)->calcPret();
        if (cumparator.getBani()<pretcrt)
            throw BaniInsuficienti();
        auto vandut = *x;
        inventar.erase(x);
        return vandut;
    }

}


//competitie
template <typename T>
class Competitie {
    std::string numeComp;
    std::vector<std::shared_ptr<T>> animComp;
    std::vector<std::shared_ptr<Antrenor<T>>> adversari;
    Jucator jucator;
    std::string tara;

    public:
    Competitie (std::string nume, const std::vector<std::shared_ptr<T>>& animComp,
        std::vector<std::shared_ptr<Antrenor<T>>> adv, Jucator  jucator, std::string tara);
};


template<typename T>
Competitie<T>::Competitie(std::string nume, const std::vector<std::shared_ptr<T> > &animComp,
    std::vector<std::shared_ptr<Antrenor<T>>> adv, Jucator jucator, std::string tara): numeComp(std::move(nume)), animComp(animComp),
adversari(adv),jucator(std::move(jucator)), tara(std::move(tara)) {

}

class Meniu {
    Jucator player{"Andrei", {}};
public:
    void ruleaza();
private:
    static void afisOptiuni() ;
    static void comandaAdaugaMagazin();
    static void comandaAfisMagazin() ;
    void comandaCumpara();
    void comandaAfisJucator() const;
    void comandaAntreneaza() const;
};

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
              << "alege optiunea: ";
}

void Meniu::comandaAdaugaMagazin() {
    auto& shop = Magazin::instanta();
    shop.adaugaAnimal(std::make_shared<Cal>("Sigma", 5, std::set<std::string>{"viteza"}, 1, 80, 90, "Epic"));
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

int main() {
    Meniu meniu;
    meniu.ruleaza();
    return 0;
}

//TODO de verificat si corectat exceptii
//TODO de adaugat functii pentru competitii
//TODO de schimbat anumite functii
//TODO de actualizat meniul
