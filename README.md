# Animal Smart Race

## Descriere

In acest proiect tu ca jucator vei avea grija de niste animale(cai sau caini). Poti antrena animalele si sa participi cu ele la competitii.

Fiecare specie de animal se antreneaza diferit si iti ofera diferite beneficii. Caii pot produce bani, iar cainii iti cresc popularitatea.

Animalele se cumpara din magazin si pot fi upgradate de jucator in urma unui calcul al costului de upgrade(diferit in functie de specie).

In ziua competitiei, alegi sa participi cu un animal pentru o anumita cursa. La aceasta cursa participa si alti oponenti care detin animalele lor.

Oponetii au o strategie bazata pe cel mai popular participant din cursa, deoarece fiecare competitie are un sistem de calculare al castigatorului.

Se verifica 3 lucruri: performanta totala (calculata diferit pentru fiecare specie), avantajul(un sistem in stilul piatra-foarfeca-hartie) si ca tie-breaker se ia valoarea unui atribut specific speciei pentru o anumita competitie.

Jucatorul(Om) poate sa decida sa nu mai participe la concurs si sa ii lase pe oponentii sai sa se intreaca.


## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# sau ./scripts/cmake.sh configure
```

Sau pe Windows cu GCC:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.


