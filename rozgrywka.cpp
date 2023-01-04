#include "rozgrywka.h"


bool rozgrywka(int rozmiar, int ilosc_wrzedzie, int glebokosc, bool czy_komp_zaczyna){

    gra GRA1(rozmiar, ilosc_wrzedzie);

    c_GUI GUI(rozmiar);
    GUI.rysuj_plansze(GRA1);
    sf::Event zdarzenie;
    char wygrany;

    while(!GRA1.czyWygral(GRACZ) && !GRA1.czyWygral(KOMP) && GRA1.czyJestMiejsce()){
        if(!czy_komp_zaczyna)
            GUI.wczytaj_ruch_gracza(GRA1);
        czy_komp_zaczyna = false;

        if(GRA1.czyWygral(GRACZ) || GRA1.czyWygral(KOMP) || !GRA1.czyJestMiejsce())
            break;

//***************************************************************
        minmaxf(GRA1, true, glebokosc, -NIESKO, NIESKO);
//****************************************************************

        GRA1.dodajRuchKomp();
        GUI.dodaj_ruch_kompa(GRA1.zwrocRuch());
        GUI.wyswietl_stan(GRA1);

    }
    GUI.wyswietl_stan(GRA1);

    //sprawdzenie i wyswietlenie wygranego (remisu)
    if(GRA1.czyWygral(KOMP))
        wygrany = KOMP;
    else if(GRA1.czyWygral(GRACZ))
        wygrany = GRACZ;
    else
        wygrany = 'R';

    if(GUI.zwrocOkno().isOpen()){
        GUI.wyswietl_wygranego(wygrany);
        GUI.zwrocOkno().display();
    }

    bool jeszcze_raz = false;
    while(GUI.zwrocOkno().isOpen() && !jeszcze_raz){  //czekanie na zamkniecie okna lub nacisniecie przycisku
         while (GUI.zwrocOkno().pollEvent(zdarzenie)){
            if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left){
                jeszcze_raz = true;
                }
            if (zdarzenie.type == sf::Event::Closed)
                GUI.zwrocOkno().close();
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape )
                GUI.zwrocOkno().close();

         }
    }
return jeszcze_raz;
}

