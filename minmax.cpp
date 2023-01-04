#include "minmax.h"


int minmaxf(gra &GRA, bool czyKomputer, int glebokosc, int alfa, int beta){

    c_ruch ruch;        //ruch dla komputera

    if(GRA.czyWygral(GRACZ))  //czy wygral gracz
        return -NIESKO+1;
    if(GRA.czyWygral(KOMP))   //czy wygral komputer
        return NIESKO-1;
    if(!GRA.czyJestMiejsce())
        return 0;      //remis

    if (glebokosc == 0)
        return GRA.f_heurystyczna(czyKomputer) + GRA.f_heurystyczna(!czyKomputer);

    int rozmiar_planszy = GRA.zwrocRozmiar();
    bool wyjdz_z_petli = false;

    if(czyKomputer){
        int wartosc = -NIESKO;
        for(int i=0; i<rozmiar_planszy && !wyjdz_z_petli; i++)
            for(int j=0; j<rozmiar_planszy && !wyjdz_z_petli; j++)
                if(GRA.czy_ruch_mozliwy(i, j)){
                    GRA.wstawZnak(i, j, KOMP);
                    int nowa_wartosc = minmaxf(GRA, false, glebokosc-1, alfa, beta);
                    GRA.wstawZnak(i, j, PUSTE_POLE);
                    if (nowa_wartosc > wartosc){
                        ruch.w = i;   ruch.k = j;  //aktualizacja potencjalnego ruchu komputera
                        wartosc = nowa_wartosc;
                    }
                    if (nowa_wartosc > alfa)
                        alfa = nowa_wartosc;
                    if (beta <= alfa)
                        wyjdz_z_petli = true;
                }
        GRA.ustawRuch(ruch.w, ruch.k);  //ustawienie ruchu, ktory bedzie wykonany przez komputer
        return wartosc;
    } else{
        int wartosc = NIESKO;
        for(int k=0; k<rozmiar_planszy && !wyjdz_z_petli; k++)
            for(int p=0; p<rozmiar_planszy && !wyjdz_z_petli; p++)
                if(GRA.czy_ruch_mozliwy(k, p)){
                    GRA.wstawZnak(k, p, GRACZ);
                    int nowa_wartosc = minmaxf(GRA, true, glebokosc-1, alfa, beta);
                    GRA.wstawZnak(k, p, PUSTE_POLE);
                    if (nowa_wartosc < wartosc){
                        wartosc = nowa_wartosc;
                    }
                    if (nowa_wartosc < beta)
                        beta = nowa_wartosc;
                    if (beta <= alfa)
                        wyjdz_z_petli = true;
                }
        return wartosc;
    }
}

