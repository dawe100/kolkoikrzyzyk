#include "f_heurystyczna.h"


int f_wyliczjaca(int wypel, int puste, int ilosc_wrzedzie){
    int wynik;

    if ((ilosc_wrzedzie-puste-wypel) > 0)  //gdy na pewno nie wygra
        return 0;


    wynik = wypel*M_GR;

return wynik;
}


int gra::f_heurystyczna(bool czy_komputer){
    int wynik_koncowy = 0;

    char  obecny_gracz;
    int mnoz_gracza;

    if(!czy_komputer){
        obecny_gracz = GRACZ;
        mnoz_gracza = -1;
    }
    else{
        obecny_gracz = KOMP;
        mnoz_gracza = 1;
    }

    int wynik_temp = 0;
    int puste_temp = 0;
    bool p;


    //wiersze
    for(int w=0; w<rozmiar_pola; w++){
        for(int k=0; k<rozmiar_pola; k++){
            while(k < rozmiar_pola && ((p=(pole_gry[w][k] == PUSTE_POLE)) || pole_gry[w][k] == obecny_gracz)){
                if(p){
                    puste_temp++;
                }else
                    wynik_temp++;
                k++;
            }

            if(wynik_temp !=0 && puste_temp !=0)
               wynik_koncowy = wynik_koncowy + f_wyliczjaca(wynik_temp, puste_temp, ilosc_wrzedzie);
            wynik_temp = 0;  //zerowanie gdy w polu jest znak przeciwnika
            puste_temp = 0;  //zerowanie gdy w polu jest znak przeciwnika
        }
    }


    //kolumny
    for(int k=0; k<rozmiar_pola; k++){
        for(int w=0; w<rozmiar_pola; w++){
            while(w < rozmiar_pola && ((p=pole_gry[w][k] == PUSTE_POLE) || pole_gry[w][k] == obecny_gracz)){
                if(p)
                    puste_temp++;
                else
                    wynik_temp++;
                w++;
            }

            if(wynik_temp !=0 && puste_temp !=0)
                wynik_koncowy = wynik_koncowy + f_wyliczjaca(wynik_temp, puste_temp, ilosc_wrzedzie);
            wynik_temp = 0;  //zerowanie gdy w polu jest znak przeciwnika
            puste_temp = 0;  //zerowanie gdy w polu jest znak przeciwnika
        }
    }



    //przekatne
    for(int k=0; k<rozmiar_pola; k++){
        for(int w=0; w<rozmiar_pola; w++){
            int tmp_w = w, tmp_k = k;
            while(w < rozmiar_pola && k < rozmiar_pola && ((p=pole_gry[w][k] == PUSTE_POLE) || pole_gry[w][k] == obecny_gracz)){
                if(p)
                    puste_temp++;
                else
                    wynik_temp++;
                w++, k++;
            }
            w = tmp_w; k = tmp_k;

            if(wynik_temp !=0 && puste_temp !=0)
                wynik_koncowy = wynik_koncowy + f_wyliczjaca(wynik_temp, puste_temp, ilosc_wrzedzie);
            wynik_temp = 0;  //zerowanie gdy w polu jest znak przeciwnika
            puste_temp = 0;  //zerowanie gdy w polu jest znak przeciwnika
        }
    }


    //przekatne wsteczne
    for(int k=rozmiar_pola-1; k>=0; k--){
        for(int w=0; w<rozmiar_pola; w++){
            int tmp_w = w, tmp_k = k;
            while(w < rozmiar_pola && k >=0 && ((p=pole_gry[w][k] == PUSTE_POLE) || pole_gry[w][k] == obecny_gracz)){
                if(p)
                    puste_temp++;
                else
                    wynik_temp++;
                w++, k--;
            }
            w = tmp_w; k = tmp_k;

            if(wynik_temp !=0 && puste_temp !=0)
                wynik_koncowy = wynik_koncowy + f_wyliczjaca(wynik_temp, puste_temp, ilosc_wrzedzie);
            wynik_temp = 0;  //zerowanie gdy w polu jest znak przeciwnika
            puste_temp = 0;  //zerowanie gdy w polu jest znak przeciwnika
        }
    }


return wynik_koncowy * mnoz_gracza;
}
