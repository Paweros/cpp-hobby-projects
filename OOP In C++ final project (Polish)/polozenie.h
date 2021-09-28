#ifndef POLOZENIE_H_INCLUDED
#define POLOZENIE_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//Spis klas
class Polozenie;
//class Polozenie_Kulki:public Polozenie;
class Kulka;
//class Taran:public Kulka;
//class Wybuchowa:public Kulka;
class Odbijacz;
//class UkosnyL:public Kulka;
//class UkosnyP:public Kulka;
//class Losowy:public Kulka;
//class Zjadajacy:public Kulka;
//class Spowalniajacy:public Kulka;
//class Mglowy:public Kulka;
//class Przyspieszajacy:public Kulka;
class Plansza;
//~Spis klas

//Klasy
class Polozenie
{
protected:
    int x;
    int y;
public:
    //konstruktory
    Polozenie(int _x, int _y) :x(_x), y(_y) {};
    Polozenie() = delete;//tak dla spokoju
    Polozenie(const Polozenie& p) {
        x = p.x;
        y = p.y;
    };
    Polozenie operator =(const Polozenie& p) {
        x = p.x;
        y = p.y;
        return *this;
    };
    //destruktor
    ~Polozenie() = default;
    //metody
    bool operator == (const Polozenie&) const;
    int& operator[](int i);//dostep do x,y
    friend ostream& operator<< (ostream& os, const Polozenie& p);
};

class Polozenie_Kulki : public Polozenie
{
protected:
    Polozenie* obrot;//konstruktor dba o to, aby x,y przyjmowaly wartosci {-1,0,1}
    int turyNaRuch;// 1/predkosc
    int ileWMiejscu;// licznik do kolejnego ruchu
public:
    //ko nstruktory
    Polozenie_Kulki(int _x, int _y, int _dx, int _dy, int tNR = 1) :Polozenie(_x, _y) {
        if (_dx != 0) _dx /= abs(_dx);
        if (_dy != 0) _dy /= abs(_dy);
        obrot = new Polozenie(_dx, _dy);
        turyNaRuch = tNR;
        ileWMiejscu = 0;
    };
    Polozenie_Kulki() = delete;//tak dla spokoju
    Polozenie_Kulki(const Polozenie_Kulki& p) = delete;
    Polozenie_Kulki operator =(const Polozenie& p) = delete;
    //destruktor
    ~Polozenie_Kulki() {
        delete obrot;
    };
    //metody
    Polozenie* dajObrot();
    int dajSzybkosc();
    void ustawSzybkosc(int);
    void odbij();//z powrotem
    void obrocP();//jak przy zderzeniu z odbijaczem (U)kosnym
    void obrocL();//jak przy zderzeniu z odbijaczem (u)kosnym
    bool ruch();
    friend ostream& operator<< (ostream& os, const Polozenie_Kulki& p);
};
//~Klasy

//Implementacja

//Polozenie
int& Polozenie::operator[](int i) {
    if (i == 0) return x;
    return y;
}
bool Polozenie::operator == (const Polozenie& p) const {
    return(x == p.x && y == p.y);
}
ostream& operator<< (ostream& os, const Polozenie& p) {
    return os << "(" << p.x << " " << p.y << ")";
}
//Polozenie_Kulki
Polozenie* Polozenie_Kulki::dajObrot() {
    return obrot;
};
int Polozenie_Kulki::dajSzybkosc() {
    return turyNaRuch;
}
void Polozenie_Kulki::ustawSzybkosc(int s) {
    turyNaRuch = s;
}
void Polozenie_Kulki::odbij() {
    (*obrot)[0] *= -1;
    (*obrot)[1] *= -1;
};
void Polozenie_Kulki::obrocP() {//jak przy zderzeniu z odbijaczem (U)kosnym
    int t = (*obrot)[0];
    (*obrot)[0] = -(*obrot)[1];
    (*obrot)[1] = -t;
};
void Polozenie_Kulki::obrocL() {//jak przy zderzeniu z odbijaczem (u)kosnym
    int t = (*obrot)[0];
    (*obrot)[0] = (*obrot)[1];
    (*obrot)[1] = t;
};
bool Polozenie_Kulki::ruch() {
    if (++ileWMiejscu >= turyNaRuch)
    {
        (*this)[0] += (*obrot)[0];
        (*this)[1] += (*obrot)[1];
        ileWMiejscu = 0;
    }
    return !ileWMiejscu;
}
ostream& operator<< (ostream& os, const Polozenie_Kulki& p) {
    return os << (Polozenie)p << ", obrocona " << *p.obrot;
}
//~Polozenie_Kulki
//~Polozenie
//~Implementacja
#endif // POLOZENIE_H_INCLUDED
#pragma once
