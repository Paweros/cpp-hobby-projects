#include <time.h>
#include "plansza.h"
#include "polozenie.h"
#include <sstream>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])

{
    srand(time(NULL));
    string filepath = (argc > 0 ? argv[1] : "test.txt");
    Plansza* p = new Plansza(filepath);
    int typ_wysw = 1;
    if (argc >= 2)
    {
        istringstream iss(argv[2]);
        iss >> typ_wysw;
    }
    p->start(typ_wysw);
    delete p;
    return 0;
}
