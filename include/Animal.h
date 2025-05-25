//
// Created by razvan on 5/23/25.
//

#ifndef ANIMAL_H
#define ANIMAL_H
#include <memory>
#include <string>


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

    [[nodiscard]] virtual int getObstacole() const = 0;
    [[nodiscard]] virtual int getSprint() const = 0;
    [[nodiscard]] std::string getNume() const;
    void crestePart();
};


#endif //ANIMAL_H
