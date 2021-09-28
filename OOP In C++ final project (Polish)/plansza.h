#ifndef PLANSZA_H_INCLUDED
#define PLANSZA_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

///Wyswietlanie:
//0 - bez wyswietlania
#define TRYB_WYSW_1 0//0 - wyswietl stan kulek pod koniec symulacji
#define TRYB_WYSW_2 1//1 - wyswietl stan kulek pod koniec kazdej tury
#define TRYB_WYSW_3 2//2 - wyswietl stan kulek i odbijaczy pod koniec tury
                     //3+ - wyswietl stan pod koniec tury, przejscia i interakcje

using namespace std;

///Spis klas
#include "polozenie.h"
    //class Polozenie;
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
///~Spis klas

///Struktura klas

class Kulka //Zwykla
{
protected:
    Plansza* plansza;
    Polozenie_Kulki* pol;
    int ID;
    int czas;
    bool czyWypadla;
    bool czyZniszczona;
public:
    //konstruktory
    Kulka(int _x, int _y, int _rotx = 0, int _roty = 0) {
        plansza = nullptr;
        ID = -1;
        pol = new Polozenie_Kulki(_x, _y, _rotx, _roty);
        czas = 0;
        czyWypadla = 0;
        czyZniszczona = 0;
    }
    Kulka(Polozenie_Kulki* _pol) {
        plansza = nullptr;
        ID = -1;
        pol = _pol;
        czas = 0;
        czyWypadla = 0;
        czyZniszczona = 0;
    }
    Kulka() = delete;
    Kulka(const Polozenie_Kulki& p) = delete;
    Kulka operator =(const Polozenie& p) = delete;
    //destruktor
    virtual ~Kulka() {
        delete pol;
    }
    //metody
        //get
    Polozenie_Kulki* dajPol();
    void ustawPol(Polozenie_Kulki*, bool);
    int dajID();
    int dajCzas();
    bool wypadla();
    bool zniszczona();
    //set
    void ustawID(int);
    //inne
    void naPlansze(Plansza*);
    void odbij(Kulka*, int);
    virtual void zderz(int);
    void ruch(int);
    void zniszcz();
    virtual string dajTyp() {
        return "Zwykla";
    };
    friend ostream& operator<< (ostream& os, Kulka& k) {
        return os << "Kulka " << k.dajID() << " (" << k.dajTyp() << ")";
    };
};

class Taran :public Kulka
{
public:
    Taran(int _x, int _y, int _rotx = 0, int _roty = 0) :Kulka(_x, _y, _rotx = 0, _roty = 0) {};
    Taran(Polozenie_Kulki* pol) :Kulka(pol) {};
    ~Taran() = default;
    void zderz(int);
    virtual string dajTyp() {
        return "Taran";
    };
};

#define PORAWYBUCHU 6
class Wybuchowa :public Kulka
{
public:
    Wybuchowa(int _x, int _y, int _rotx = 0, int _roty = 0) :Kulka(_x, _y, _rotx = 0, _roty = 0) {};
    Wybuchowa(Polozenie_Kulki* pol) :Kulka(pol) {};
    ~Wybuchowa() = default;
    void zderz(int);
    virtual string dajTyp() {
        return "Wybuchowa";
    };
};

class Odbijacz
{
protected:
    Plansza* plansza;
    Polozenie* pol;
    bool czyZniszczony;
public:
    //konstruktor
    Odbijacz(int _x, int _y)
    {
        plansza = nullptr;
        pol = new Polozenie(_x, _y);
        czyZniszczony = 0;
    }
    Odbijacz(Polozenie* _pol)
    {
        plansza = nullptr;
        pol = _pol;
        czyZniszczony = 0;
    }
    //destruktor
    virtual ~Odbijacz() {
        delete pol;
    };
    //metody
        //get
    Polozenie* dajPol();
    bool zniszczony();
    //inne
    virtual void odbij(Kulka*, int) {};
    void zniszcz(int);
    void naPlansze(Plansza* p);
    virtual string dajTyp() {
        return "";
    };
    friend ostream& operator<< (ostream& os, Odbijacz& o) {
        return os << "Odbijacz (" << o.dajTyp() << ")";
    };
};

class UkosnyL :public Odbijacz
{
public:
    UkosnyL(int x, int y) :Odbijacz(x, y) {};
    UkosnyL(Polozenie* _pol) :Odbijacz(_pol) {};
    ~UkosnyL() = default;
    void odbij(Kulka*, int);
    virtual string dajTyp() {
        return "Ukosny[\\]";
    };
};

class UkosnyP :public Odbijacz
{
public:
    UkosnyP(int x, int y) :Odbijacz(x, y) {};
    UkosnyP(Polozenie* _pol) :Odbijacz(_pol) {};
    ~UkosnyP() = default;
    void odbij(Kulka*, int);
    virtual string dajTyp() {
        return "Ukosny[/]";
    };
};

class Losowy :public Odbijacz
{
public:
    Losowy(int x, int y) :Odbijacz(x, y) {};
    Losowy(Polozenie* _pol) :Odbijacz(_pol) {};
    ~Losowy() = default;
    void odbij(Kulka*, int);
    virtual string dajTyp() {
        return "Losowy";
    };
};

class Zjadajacy :public Odbijacz
{
public:
    Zjadajacy(int x, int y) :Odbijacz(x, y) {};
    Zjadajacy(Polozenie* _pol) :Odbijacz(_pol) {};
    ~Zjadajacy() = default;
    void odbij(Kulka*, int);
    virtual string dajTyp() {
        return "Zjadajacy";
    };
};

class Mglowy :public Odbijacz
{
public:
    Mglowy(int x, int y) :Odbijacz(x, y) {};
    Mglowy(Polozenie* _pol) :Odbijacz(_pol) {};
    ~Mglowy() = default;
    void odbij(Kulka*, int);
    virtual string dajTyp() {
        return "Mglowy";
    };
};

class Spowalniajacy :public Odbijacz
{
public:
    Spowalniajacy(int x, int y) :Odbijacz(x, y) {};
    Spowalniajacy(Polozenie* _pol) :Odbijacz(_pol) {};
    ~Spowalniajacy() = default;
    void odbij(Kulka*, int);
    virtual string dajTyp() {
        return "Spowalniajacy";
    };
};

class Przyspieszajacy :public Odbijacz
{
public:
    Przyspieszajacy(int x, int y) :Odbijacz(x, y) {};
    Przyspieszajacy(Polozenie* _pol) :Odbijacz(_pol) {};
    ~Przyspieszajacy() = default;
    void odbij(Kulka*, int);
    virtual string dajTyp() {
        return "Przyspieszajacy";
    };
};

class Plansza
{
protected:
    Polozenie* rozmiar; //gra toczy sie na polach od 1,1 do n,k, rzeczywiste rozmiary to n+2,k+2;
    vector<Kulka*> kulki;
    int liczbaKulek;
    vector<Odbijacz*> odbijacze;
    int czas;
    int czasStopu;
public:
    //konstruktory
    Plansza(int c, int n, int m)
    {
        czas = 0;
        czasStopu = c;
        rozmiar = new Polozenie(n, m);
        liczbaKulek = 0;
    }
    Plansza(string filepath);
    Plansza() = delete;
    Plansza operator = (const Plansza& p)
    {
        rozmiar = p.rozmiar;
        liczbaKulek = p.liczbaKulek;
        kulki = p.kulki;
        odbijacze = p.odbijacze;
        return *this;
    }
    //destruktor
    ~Plansza() {
        delete rozmiar;
        kulki.erase(kulki.begin(), kulki.end());
        odbijacze.erase(odbijacze.begin(), odbijacze.end());
    }
    vector<Odbijacz*> dajOdbijacze(Polozenie*);
    vector<Kulka*> dajKulki(Polozenie*, int);
    vector<Kulka*> dajKulki();
    void dodajKulke(Kulka*);
    bool usunKulke(Kulka*);
    void dodajOdbijacz(Odbijacz*);
    bool usunOdbijacz(Odbijacz*);
    void zrobKulke(Polozenie_Kulki*, char);
    void zrobOdbijacz(Polozenie*, char);
    void wczytaj(fstream&, string);
    void ruch(int);
    bool pozaGranicami(Kulka*);
    void wypisz(int);
    void ladujPlansze();
    void start(int wypisuj);
};

///~Struktura klas

///Implementacja

//Kulka
int Kulka::dajID() {
    return ID;
}

Polozenie_Kulki* Kulka::dajPol() {
    return pol;
}

void Kulka::ustawPol(Polozenie_Kulki* p, bool czyNiszcz = 1) {
    if (czyNiszcz) delete pol;
    pol = p;
}

bool Kulka::wypadla() {
    return czyWypadla;
}
bool Kulka::zniszczona() {
    return czyZniszczona;
}

int Kulka::dajCzas() {
    return czas;
}

void Kulka::naPlansze(Plansza* p) {
    plansza = p;
    p->dodajKulke(this);
}

void Kulka::ustawID(int _ID) {
    ID = _ID;
}

void Kulka::ruch(int wypisuj = 0) {
    if (!wypadla() && !zniszczona()) {
        if (pol->ruch())
        {
            if (wypisuj > TRYB_WYSW_3) {
                cout << *this << " rusza sie do " << *pol << endl;
            }
            zderz(wypisuj);
        }
        czas++;
        if (plansza->pozaGranicami(this)) {
            if (wypisuj > TRYB_WYSW_3) {
                cout << *this << " rusza sie do " << *pol << endl;
                }
            czyWypadla = 1;
        }
    }
}

void Kulka::odbij(Kulka* k, int wypisuj = 0) {
    Polozenie_Kulki* p = pol;
    p = k->dajPol();
    k->ustawPol(p, 0);
    if (wypisuj > TRYB_WYSW_3) cout << "Kulki " << dajID() << " i " << k->dajID() << " zderzaja sie" << endl;
}

void Kulka::zderz(int wypisuj = 0) {
    vector<Odbijacz*> o = plansza->dajOdbijacze(pol);
    for (auto& it : o)
    {
        if (!(it->zniszczony()))
            it->odbij(this, wypisuj);
    }
    vector<Kulka*> k = plansza->dajKulki(pol, ID);
    for (auto& it : k)
    {
        if (!(it->zniszczona()))
            if (it->dajID() != ID)
                it->odbij(this, wypisuj);
    }
}

void Kulka::zniszcz() {
    czyZniszczona = 1;
}

//Taran
void Taran::zderz(int wypisuj = 0) {
    vector<Odbijacz*> o = plansza->dajOdbijacze(pol);
    for (auto& it : o)
    {
        it->zniszcz(wypisuj);
    }
    vector<Kulka*> k = plansza->dajKulki(pol, ID);
    for (auto& it : k)
    {
        if (it->dajID() != ID)
            it->odbij(this, wypisuj);
    }
}

//~Taran

//Wybuchowa
void Wybuchowa::zderz(int wypisuj = 0) {
    vector<Odbijacz*> o = plansza->dajOdbijacze(pol);

    if (czas == PORAWYBUCHU)
    {
        if (wypisuj > TRYB_WYSW_3)
            cout << "...i wybucha" << endl;
        for (auto& it : o)
        {
            it->zniszcz(wypisuj);
        }
        zniszcz();
    }
    else
    {
        for (auto& it : o)
        {
            it->odbij(this, wypisuj);
        }
        vector<Kulka*> k = plansza->dajKulki(pol, ID);
        for (auto& it : k)
        {
            if (it->dajID() != ID)
                it->odbij(this, wypisuj);
        }
    }
}

//~Wybuchowa

//~Kulka

//Odbijacz

Polozenie* Odbijacz::dajPol() {
    return pol;
}

bool Odbijacz::zniszczony() {
    return czyZniszczony;
}

void Odbijacz::naPlansze(Plansza* p) {
    plansza = p;
    p->dodajOdbijacz(this);
}

void Odbijacz::zniszcz(int wypisuj = 0) {
    if (wypisuj > TRYB_WYSW_3)
        cout << "... niszczac " << *this << endl;
    czyZniszczony = 1;
}

//UkosnyL
void UkosnyL::odbij(Kulka* k, int wypisuj = 0) {
    k->dajPol()->obrocL();
    if (wypisuj > TRYB_WYSW_3)
        cout << "...i odbija sie w kierunku " << *(k->dajPol()->dajObrot()) << endl;
}

//~UkosnyL

//UkosnyP
void UkosnyP::odbij(Kulka* k, int wypisuj = 0) {
    k->dajPol()->obrocP();
    if (wypisuj > TRYB_WYSW_3)
        cout << "...i odbija sie w kierunku " << *(k->dajPol()->dajObrot()) << endl;
}

//~UkosnyP

//Losowy
void Losowy::odbij(Kulka* k, int wypisuj = 0) {
    Polozenie_Kulki* pol = k->dajPol();
    int r = rand() % 8;
    if (r > 3) r++;
    (*pol->dajObrot())[0] = r % 3 - 1;
    (*pol->dajObrot())[1] = r / 3 - 1;
    if (wypisuj > TRYB_WYSW_3)
        cout << "...i odbija sie losowo w kierunku " << *pol->dajObrot() << endl;
}

//~Losowy

//Zjadajacy
void Zjadajacy::odbij(Kulka* k, int wypisuj = 0) {
    if (wypisuj > TRYB_WYSW_3)
        cout << "...i zostaje zjedzona przez odbijacz" << endl;
    k->zniszcz();
}

//~Zjadajacy

//Mglowy
void Mglowy::odbij(Kulka* k, int wypisuj = 0) {
    if (wypisuj > TRYB_WYSW_3)
        cout << "...i przelatuje przez mglowy odbijacz" << endl;
}

//~Mglowy

//Spowalniajacy
void Spowalniajacy::odbij(Kulka* k, int wypisuj = 0) {
    Polozenie_Kulki* p = k->dajPol();
    p->ustawSzybkosc(p->dajSzybkosc() * 2);
    if (wypisuj > TRYB_WYSW_3)
        cout << "...i zostaje spowolniona (predkosc 1/" << p->dajSzybkosc() << ")" << endl;
}

//~Spowalniajacy

//Przyspieszajacy
void Przyspieszajacy::odbij(Kulka* k, int wypisuj = 0) {
    Polozenie_Kulki* p = k->dajPol();
    p->ustawSzybkosc((p->dajSzybkosc() + 1) / 2);
    if (wypisuj > TRYB_WYSW_3)
        cout << "...i zostaje przyspieszona (predkosc 1/" << p->dajSzybkosc() << ")" << endl;
}

//~Przyspieszajacy

//~Odbijacz

//Plansza
vector<Odbijacz*> Plansza::dajOdbijacze(Polozenie* p) {
    vector <Odbijacz*> naPolu;
    for (auto& it : odbijacze) {
        if (*(it->dajPol()) == *p) {
            naPolu.push_back(it);
        }
    }
    return naPolu;
}

vector<Kulka*> Plansza::dajKulki() {
    vector <Kulka*> naPolu;
    for (auto& it : kulki) {
        naPolu.push_back(it);
    }
    return naPolu;
}

vector<Kulka*> Plansza::dajKulki(Polozenie* p, int ID) {
    vector <Kulka*> naPolu;
    for (auto& it : kulki) {
        if (*(it->dajPol()) == *p) {
            naPolu.push_back(it);
        }
    }
    return naPolu;
}

void Plansza::dodajKulke(Kulka* k) {
    kulki.push_back(k);
    k->ustawID(liczbaKulek);
    liczbaKulek++;
}

void Plansza::dodajOdbijacz(Odbijacz* o) {
    odbijacze.push_back(o);
}

void Plansza::zrobKulke(Polozenie_Kulki* p, char c) {
    Kulka* k = nullptr;
    switch (c)
    {
    case 'Z':
        k = new Kulka(p);
        break;
    case 'W':
        k = new Wybuchowa(p);
        break;
    case 'T':
        k = new Taran(p);
        break;
    default:;
    }
    if (k != nullptr) k->naPlansze(this);
}

void Plansza::zrobOdbijacz(Polozenie* p, char c) {
    Odbijacz* o = nullptr;
    switch (c)
    {
    case 'U':
        o = new UkosnyL(p);
        break;
    case 'u':
        o = new UkosnyP(p);
        break;
    case 'L':
        o = new Losowy(p);
        break;
    case 'Z':
        o = new Zjadajacy(p);
        break;
    case 'S':
        o = new Spowalniajacy(p);
        break;
    case 'M':
        o = new Mglowy(p);
        break;
    case 'P':
        o = new Przyspieszajacy(p);
        break;
    default:;
    }
    if (o != nullptr) o->naPlansze(this);
}

Plansza::Plansza(string filepath) {
    fstream fin;
    fin.open(filepath);
    if (!fin) {
        cerr << "Nie mozna otworzyc " << filepath << endl;
        exit(1);
    }
    czas = 0;
    int n;
    int m;
    fin >> czasStopu;
    fin >> n;
    fin >> m;
    if (!fin.good())
    {
        cerr << "Niepoprawny format pliku " << filepath << endl;
        exit(1);
    }
    rozmiar = new Polozenie(n, m);
    liczbaKulek = 0;
    char c;
    for (int i = 0; i < n + 2; i++) {
        fin.get(c);
        if (c != '\n')
        {
            cerr << "Niepoprawny format pliku " << filepath << endl;
            exit(1);
        }
        for (int j = 0; j < m + 2; j++) {
            Polozenie_Kulki* pk = new Polozenie_Kulki(j, i, (j == 0 ? 1 : (j == m + 1 ? -1 : 0)), (i == 0 ? 1 : (i == n + 1 ? -1 : 0)));
            if (!fin.good())
            {
                cerr << "Niepoprawny format pliku " << filepath << endl;
                exit(1);
            }
            fin.get(c);
            if (i == 0 || j == 0 || i == n + 1 || j == m + 1) zrobKulke(pk, c);
            else zrobOdbijacz(pk, c);
        }
    }
    fin.close();
}

void Plansza::ruch(int wypisuj = 0) {
    wypisz(wypisuj);
    for (auto& it : kulki) {
        it->ruch(wypisuj);
    }
}

void Plansza::wypisz(int wypisuj = 0) {
    if (wypisuj > TRYB_WYSW_1 || czas == czasStopu)
    {
        cout << endl << "Jest tura " << czas << ":" << endl;
        for (auto& it : kulki) {
            if (it->wypadla()) {
                cout << *it << " wypadla w pozycji " << *(it->dajPol()) << " w czasie " << it->dajCzas() << endl;
            }
            else if (it->zniszczona()) {
                cout << *it << " zostala zniszczona w pozycji " << *(it->dajPol()) << " w czasie " << it->dajCzas() << endl;
            }
            else {
                cout << *it << " jest w pozycji " << *(it->dajPol()) << endl;
            }
        }
    }
    if (wypisuj > TRYB_WYSW_2)
    {
        for (auto& it : odbijacze) {
            if (!it->zniszczony()) {
                cout << *it << " jest w pozycji " << *(it->dajPol()) << endl;
            }
        }
        cout << endl;
    }
}

bool Plansza::pozaGranicami(Kulka* k) {
    bool naX = (*(k->dajPol()))[0]<1 || (*(k->dajPol()))[0]>(*rozmiar)[0];
    bool naY = (*(k->dajPol()))[1]<1 || (*(k->dajPol()))[1]>(*rozmiar)[1];
    return naX || naY;
}

void Plansza::start(int wypisuj = 0)
{
    for (; czas < czasStopu; ++czas)
    {
        ruch(wypisuj);
    }
    wypisz(wypisuj);
}
//~Plansza

///~Implementacja


#endif // PLANSZA_H_INCLUDED
