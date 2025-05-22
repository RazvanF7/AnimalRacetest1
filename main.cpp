#include <iostream>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <exception>
#include <algorithm>
#include <map>

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
    std::string avantaj;
    int initPerf;
    int pret;

protected:
    int nivel;
    virtual void afis(std::ostream&) const{}
    [[nodiscard]] virtual int extraPret() const;
    int participari;
    int energie;
    [[nodiscard]] int getInitPerf() const;
    [[nodiscard]] virtual int extraPerf() const;

public:
    Animal();
    Animal(std::string  nume, int participari, std::string av, int nivel);
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


    friend bool operator<(const Animal& a, const Animal& b);

    friend bool operator==(const Animal& a, const Animal& b);

    [[nodiscard]] int getId() const;

    virtual void antrenamentANTR() = 0;

    virtual int calculeazaPerf();

    virtual int actiuneSpeciala() = 0;

    [[nodiscard]] std::string getAvantaj() const;

    [[nodiscard]] int getParticipari() const;
};
int Animal::nextId = 0;
Animal::Animal():id(++nextId), nume("unknown"), avantaj({"unknown"}),
                    initPerf(100), pret(0), nivel(1),
                  participari(0), energie(100) {
}

Animal::Animal(std::string nume, int participari, std::string av, int nivel) :
id(++nextId),nume(std::move(nume)), avantaj(std::move(av)), initPerf(100),
pret(0), nivel(nivel), participari(participari), energie(100) {
}


Animal &Animal::operator=(const Animal &other) {
    if (this != &other) {
        nume = other.nume;
        participari = other.participari;
        avantaj = other.avantaj;
        initPerf = other.initPerf;
        nivel = other.nivel;
        energie = other.energie;
        pret = other.pret;

    }
    return *this;
}

Animal &Animal::operator++(int) {
    participari++;
    return *this;
}
int Animal::extraPret() const {
    return 0;
}

int Animal::calcPret() const {
    int i = 0;
    int pretTotal = 0;
    pretTotal += extraPret();
    for ([[maybe_unused]] const auto &av : avantaj) {
        i++;
    }
    pretTotal += i*100+ nivel*100;
    return pretTotal;
}

std::ostream& operator<<(std::ostream& os, const Animal& animal) {
    os<<"nume: "<<animal.nume<<std::endl
    <<"participari: "<<animal.participari<<std::endl
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

int Animal::getInitPerf() const {
    return initPerf;
}

int Animal::calculeazaPerf() {
    int perf = initPerf;
    perf += extraPerf();
    perf += nivel*100;
    return perf;
}

int Animal::extraPerf() const{
    return 0;
}

std::string Animal::getAvantaj() const {
    return avantaj;
}

int Animal::getParticipari() const {
    return participari;
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
    Cal(bool copiteCustom,const std::string &nume, int participari, const std::string &av, int nivel, int anduranta,int viteza,const std::string &raritate);
    static bool eRaritateValida(const std::string &raritate);
    void antreneaza() override;
    void odihna()override;
    void upgradeCopite();
    [[nodiscard]] std::shared_ptr<Animal> clone() const override;
    bool operator<(const Cal& other) const;
    void antrenamentANTR() override;
    int actiuneSpeciala() override;

};



const std::set<std::string> Cal::raritati = {"Normal", "Epic", "Legendar"};
bool Cal::eRaritateValida(const std::string &raritate) {
    return raritati.find(raritate) != raritati.end();
}
Cal::Cal(bool copiteCustom, const std::string &nume, int participari, const std::string &av,
    int nivel,int anduranta,int viteza, const std::string &raritate):
Animal(nume, participari, av, nivel),
copiteCustom(copiteCustom),anduranta(anduranta),viteza(viteza),raritate(raritate)
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
    os<<"copite speciale: ";
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
    if (participari > 10)
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
    if (participari > 10)
        perf -= 500;
    return perf;
}

std::shared_ptr<Animal> Cal::clone() const {
    return std::make_shared<Cal>(*this);
}


void Cal::antrenamentANTR() {
    anduranta+=20;
    viteza+=20;
    nivel++;
}

int Cal::actiuneSpeciala() {
    int banispec = 0;
    if (energie<10) {
        throw EnergiePutina();
    }
    else {
        banispec = (anduranta+viteza)/2;
        if (copiteCustom) {
            banispec *= 2;
        }
        energie-=10;
    }
    return banispec;
}


class CalFactory {
public:
    static std::shared_ptr<Animal> createCalStart(const std::string &nume, int participari, const std::string &av,
        int nivel, int anduranta,int viteza, const std::string &raritate);
    static std::shared_ptr<Animal> createCalMid(const std::string &nume, int participari, const std::string &av,
    int nivel, int anduranta,int viteza, const std::string &raritate);
    static std::shared_ptr<Animal> createCalEnd(const std::string &nume, int participari, const std::string &av,
    int nivel, int anduranta,int viteza, const std::string &raritate);

};

std::shared_ptr<Animal> CalFactory::createCalStart(const std::string &nume,
    int participari,const std::string &av, int nivel, int anduranta,
    int viteza, const std::string &raritate) {
    return std::make_shared<Cal>(false,nume,1,"viteza",1,100,100,"Normal");

}

std::shared_ptr<Animal> CalFactory::createCalMid(const std::string &nume,
    int participari,const std::string &av, int nivel, int anduranta,
    int viteza, const std::string &raritate) {
    return std::make_shared<Cal>(false,nume,1,"agilitate",3,200,200,"Epic");

}

std::shared_ptr<Animal> CalFactory::createCalEnd(const std::string &nume,
    int participari,const std::string &av, int nivel, int anduranta,
    int viteza, const std::string &raritate) {
    return std::make_shared<Cal>(true,nume,1,"control",5,300,300,"Legendar");

}




// Clasa Caine


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
    Caine(const std::string &nume, int participari, const std::string &av, int nivel, int loialitate,int agilitate,const std::string &rasa);
    static bool eRasaValida(const std::string &rasa);
    void antreneaza() override;
    void odihna()override;
    bool operator<(const Caine& other) const;
    [[nodiscard]] std::shared_ptr<Animal> clone() const override;
    void antrenamentANTR() override;

    int actiuneSpeciala() override;
};

const std::set<std::string> Caine::rase = {"Husky", "Ogar", "Dalmatian"};
bool Caine::eRasaValida(const std::string &rasa) {
    return rase.find(rasa) != rase.end();
}
Caine::Caine(const std::string &nume, int participari, const std::string &av,
    int nivel, int loialitate, int agilitate, const std::string &rasa):
Animal(nume, participari, av, nivel),loialitate(loialitate),agilitate(agilitate),rasa(rasa)
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
void Caine::odihna() {
    if (energie>80) {
        throw EnergieMulta();

    }
    energie+=20;
    std::cout<<"Cainele s-a odihnit. Energie actuala: "<<energie<<std::endl;
}
void Caine::afis(std::ostream& os) const {
    os<<"loialitate: "<<loialitate<<std::endl;
    os<<"agilitate: "<<agilitate<<std::endl;


}

int Caine::extraPret() const {
    int pretloc = 0;
    if (rasa == "Husky")
        pretloc += 300;
    else if (rasa == "Ogar")
        pretloc += 700;
    else
        pretloc += 200;
    pretloc += loialitate/2;
    pretloc += agilitate/2;
    if (participari > 6)
        pretloc -= 400;
    return pretloc;
}
int Caine::extraPerf() const {
    int perf = 0;
    if (rasa == "Husky")
        perf += 300;
    else if (rasa == "Ogar")
        perf += 700;
    else
        perf += 200;
    perf += loialitate/2;
    perf += agilitate/2;
    if (participari > 6)
        perf -= 300;
    return perf;
}

bool Caine::operator<(const Caine& other) const{
    return (agilitate + loialitate) < (other.agilitate + other.loialitate);
}


std::shared_ptr<Animal> Caine::clone() const {
    return std::make_shared<Caine>(*this);
}

void Caine::antrenamentANTR() {
    agilitate+=100;
    loialitate+=100;
    nivel++;
}

int Caine::actiuneSpeciala() {
    int extraPop = 0;
    if (loialitate>=100 && loialitate<200) {
        extraPop+=2;
    }
    else if (loialitate>=200) {
        extraPop+=4;
    }
    return extraPop;

}



class CaineFactory {
    public:
    static std::shared_ptr<Animal> createCaineStart(const std::string &nume, int participari, const std::string &av,
        int nivel, int agilitate,int loialitate, const std::string &rasa);
    static std::shared_ptr<Animal> createCaineMid(const std::string &nume, int participari, const std::string &av,
    int nivel, int agilitate,int loialitate, const std::string &rasa);
    static std::shared_ptr<Animal> createCaineEnd(const std::string &nume, int participari, const std::string &av,
    int nivel, int agilitate,int loialitate, const std::string &rasa);

};

std::shared_ptr<Animal> CaineFactory::createCaineStart(const std::string &nume,
    int participari,const std::string &av, int nivel, int agilitate,
    int loialitate, const std::string &rasa) {
    return std::make_shared<Caine>(nume,1,"viteza",1,100,100,"Dalmatian");

}

std::shared_ptr<Animal> CaineFactory::createCaineMid(const std::string &nume,
    int participari,const std::string &av, int nivel, int agilitate,
    int loialitate, const std::string &rasa) {
    return std::make_shared<Caine>(nume,1,"agilitate",3,200,200,"Husky");

}

std::shared_ptr<Animal> CaineFactory::createCaineEnd(const std::string &nume,
    int participari,const std::string &av, int nivel, int agilitate,
    int loialitate, const std::string &rasa) {
    return std::make_shared<Caine>(nume,1,"control",5,300,300,"Ogar");

}
template<typename A>
class StrategieSelect;
class Jucator;
template<typename A>           
class Oponent {
protected:
    std::vector<std::shared_ptr<A>> animale;  
    std::string nume;
    int experienta;
    std::string taraPreferata;
    int victorii;
    virtual void afis(std::ostream& os) const = 0;
    std::shared_ptr<StrategieSelect<A>>strat;

public:
    Oponent(std::string nume,int experienta,std::vector<std::shared_ptr<A>> anim,std::string tara,std::shared_ptr<StrategieSelect<A>> strat);

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
        return strat->pick(this->animale, jucator);
    }

    void setStrategie(std::unique_ptr<StrategieSelect<A>> stratNou) {
        strat = std::move(strat);
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
Oponent<A>::Oponent(std::string nume,int experienta, std::vector<std::shared_ptr<A>> anim,
                    std::string tara, std::shared_ptr<StrategieSelect<A>> strat): animale(std::move(anim)),
                    nume(std::move(nume)), experienta(experienta), taraPreferata(std::move(tara)),victorii(0),
                    strat(std::move(strat))
{}


//Jucator

class Jucator{
    std::string nume;
    std::vector<std::shared_ptr<Animal>> inventarp;
    int bani;
    int victorii;
    int popularitate;
public:
    Jucator(std::string nume, const std::vector <std::shared_ptr<Animal>>& inventarp);

    void adaugaAnimal(const std::shared_ptr<Animal>& animal);
    void afisInventar() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Animal>>& getAnimale() const;
    [[nodiscard]] int getBani()const;
    Jucator& operator-=(int suma);
    void calcPop();
    [[nodiscard]] std::string avantajPopular(const std::vector<std::shared_ptr<Animal>>& inventarp) const;

};

Jucator::Jucator(std::string nume, const std::vector<std::shared_ptr<Animal>>& invent):
nume(std::move(nume)),bani(2000),victorii(0),popularitate(0) {
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

void Jucator::calcPop() {
    int poplinit = 0;
    for (const auto& a : inventarp) {
        if (const auto caine = std::dynamic_pointer_cast<Caine>(a)) {
            poplinit += caine->actiuneSpeciala();
        }
    }
    popularitate = poplinit + 2*victorii;
}

std::string Jucator::avantajPopular(const std::vector<std::shared_ptr<Animal>>& inventarp) const {
    std::string cmPop = inventarp[0]->getAvantaj();
    int maxPart = inventarp[0]->getParticipari();
    for (const auto &i : inventarp) {
        int part = i->getParticipari();
        if (part > maxPart) {
            maxPart = part;
            cmPop = i->getAvantaj();
        }
    }
    return cmPop;
}


template<typename A>
class StrategieSelect {
public:
    virtual ~StrategieSelect() = default;
    virtual std::shared_ptr<A> alege(std::vector<std::shared_ptr<A>> &anims,Jucator &juc) const = 0;
};


template<typename A>
class BaseStrategie: public StrategieSelect<A> {
public:
    std::shared_ptr<A> alege(std::vector<std::shared_ptr<A>> &anims,Jucator &juc) const override;
};

template<typename A>
std::shared_ptr<A> BaseStrategie<A>::alege(std::vector<std::shared_ptr<A>> &anims,Jucator &juc) const {
    auto best = anims.front();
    int bestscor = best.calculeazaPerf();
    for (const auto &a: anims) {
        int scor = a.calculeazaPerf();
        if (scor>bestscor) {
            best = a;
            bestscor = scor;
        }
    }
    return best;
}

template<typename A>
class StrategieCounter: public StrategieSelect<A> {
    const std::map<std::string, std::string> bate = {{"agilitate", "viteza"},{"viteza", "control"},
        {"control","agilitate"}};
public:
    std::shared_ptr<A> alege(std::vector<std::shared_ptr<A>> &anims,Jucator &juc) const override;

};

template<typename A>
std::shared_ptr<A> StrategieCounter<A>:: alege(std::vector<std::shared_ptr<A>> &anims, Jucator &juc) const {
    const auto jucAnimale = juc.getAnimale();
    const std::string avPop = juc.avantajPopular(jucAnimale);

    std::string counter = bate.at(avPop);

    for (const auto& a: anims) {
        if (a.getAvantaj() == counter) {
            return a;
        }
    }
    return BaseStrategie<A> {}.alege(anims, juc);

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

    std::shared_ptr<Animal> cumparaAnimal(int id, const Jucator &cumparator);

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

std::shared_ptr<Animal> Magazin::cumparaAnimal(int id, const Jucator &cumparator) {
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

template<typename A>
class Competitie {
    std::string numeComp;
    std::vector<std::shared_ptr<A>> participanti;
    std::string tara;

public:

    Competitie(std::string nume,std::vector<std::shared_ptr<A>> participanti, std::string country): numeComp(std::move(nume)),
    participanti(std::move(participanti)),tara(std::move(country)) {

    }
};

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
              << "alege optiunea: "<<std::endl;
}

void Meniu::comandaAdaugaMagazin() {
    auto& shop = Magazin::instanta();
    shop.adaugaAnimal(std::make_shared<Cal>(false,"Sigma", 5,"viteza", 1, 80, 90, "Epic"));
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
