#include "klasagry.h"


gra::gra(int rozmiar, int ilosc_wrzedzie1){

    ilosc_wrzedzie = ilosc_wrzedzie1;
    rozmiar_pola = rozmiar;
    ilosc_pustych = rozmiar*rozmiar;
    pole_gry = new char* [rozmiar];

    for (int i=0; i<rozmiar; i++){
        pole_gry[i] = new char[rozmiar];
        for(int j=0; j<rozmiar; j++)
            pole_gry[i][j] = PUSTE_POLE;
    }
}



bool gra::czyJestMiejsce(){
    for(int i=0; i<rozmiar_pola; i++)
        for(int j=0; j<rozmiar_pola; j++)
            if(pole_gry[i][j] == PUSTE_POLE)
                return true;
    return false;
}


void gra::wstawZnak(int w, int k, char znak){
    pole_gry[w][k] = znak;
    if (znak == PUSTE_POLE)
        ++ilosc_pustych;
    else
        --ilosc_pustych;
}



bool gra::czy_ruch_mozliwy(int i, int j){
    if (pole_gry[i][j] == PUSTE_POLE)
        return true;
    return false;
}


bool gra::czyWygral(char gracz){

    int ile_lacznych=0;
    char obecny_gracz;
    if(gracz == GRACZ)
        obecny_gracz = GRACZ;
    else
        obecny_gracz = KOMP;


    //wygrany wiersz
    for(int w=0; w<rozmiar_pola; w++){
        for(int k=0; k<(rozmiar_pola-(ilosc_wrzedzie-1)); k++){
            while(pole_gry[w][k] == obecny_gracz){
                ile_lacznych++; k++;
                if(ile_lacznych == ilosc_wrzedzie)
                    return true;
            }
            ile_lacznych = 0;
        }
    }

    //wygrana kolumna
    for(int k=0; k<rozmiar_pola; k++){
        for(int w=0; w<(rozmiar_pola-(ilosc_wrzedzie-1)); w++){
            while(pole_gry[w][k] == obecny_gracz){
                ile_lacznych++; w++;
                if(ile_lacznych == ilosc_wrzedzie)
                    return true;
            }
            ile_lacznych = 0;
        }
    }

    //wygrana przekatna
    for(int k=0; k<(rozmiar_pola-(ilosc_wrzedzie-1)); k++){
        for(int w=0; w<(rozmiar_pola-(ilosc_wrzedzie-1)); w++){
            while(pole_gry[w][k] == obecny_gracz){
                ile_lacznych++; w++; k++;
                if(ile_lacznych == ilosc_wrzedzie)
                    return true;
            }
            ile_lacznych = 0;
        }
    }

    //wygrana przekatna wsteczna
    for(int k=rozmiar_pola-1; k>(ilosc_wrzedzie-2); k--){
        for(int w=0; w<(rozmiar_pola-(ilosc_wrzedzie-1)); w++){
            while(pole_gry[w][k] == obecny_gracz){
                ile_lacznych++; w++; k--;
                if(ile_lacznych == ilosc_wrzedzie)
                    return true;
            }
            ile_lacznych = 0;
        }
    }

return false;
}



bool gra::dodajRuchGracza(int w, int k){
    if((w < rozmiar_pola) && (k < rozmiar_pola))
        if(pole_gry[w][k] == PUSTE_POLE){
            pole_gry[w][k] = GRACZ;
            --ilosc_pustych;
            return true;
        }
    return false;
}


bool gra::dodajRuchKomp(int w, int k){
    if((w < rozmiar_pola) && (k < rozmiar_pola))
        if(pole_gry[w][k] == PUSTE_POLE){
            pole_gry[w][k] = KOMP;
            --ilosc_pustych;
            return true;
        }
    return false;
}




void gra::drukujGre(){
    for(int w=0; w<rozmiar_pola; w++){
        for(int k=0; k<rozmiar_pola; k++){
            cout << " | ";
            switch (pole_gry[w][k])
            {
            case GRACZ:
                cout << 'X';
                break;
            case KOMP:
                cout << 'O';
                break;
            case PUSTE_POLE:
                cout << ' ';
                break;
            }
        }
        cout << " |" << endl;
    }
}
