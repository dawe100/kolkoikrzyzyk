#ifndef KLASAGRY_H_INCLUDED
#define KLASAGRY_H_INCLUDED

#include <iostream>
#define PUSTE_POLE 'P'

#define GRACZ 'G'
#define KOMP 'K'


using namespace std;

class c_ruch{
  public:
    int w;
    int k;
    c_ruch(){w=-1; k=-1;};
};

class gra{

    char **pole_gry;
    int rozmiar_pola;
    int ilosc_wrzedzie;
    int ilosc_pustych;
    c_ruch ruch;

public:
    gra(int rozmiar, int ilosc_wrzedzie1);   //konstruktor
    char**   zwrocPoleGry(){return pole_gry;};
    bool czy_ruch_mozliwy(int i, int j);
    int zwrocRozmiar()      {return rozmiar_pola;};
    void ustawRuch(int i, int j)  {ruch.w = i; ruch.k = j;};
    c_ruch zwrocRuch(){return ruch;};
    bool czyWygral(char gracz);
    bool dodajRuchGracza(int w, int k);
    bool dodajRuchKomp(int w, int k);
    void dodajRuchKomp(){if((ruch.k != -1) && (ruch.w != -1)){pole_gry[ruch.w][ruch.k] = KOMP; --ilosc_pustych;}};
    void wstawZnak(int w, int k, char znak);
    void drukujGre();
    bool czyJestMiejsce();

    int f_heurystyczna(bool czyKomputer);
};



#endif // KLASAGRY_H_INCLUDED
