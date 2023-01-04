#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "klasagry.h"
#define skala 0.95

class c_GUI{

    sf::RenderWindow oknoGry;
    sf::Sprite **tablica;

    sf::Texture kolko;
    sf::Texture krzyzyk;
    sf::Texture puste;
    sf::Texture pods;

    int rozmiar_planszy;

public:
    c_GUI(int rozmiar);
    rysuj_plansze(gra &GRA);
    c_ruch wczytaj_ruch_gracza(gra &GRA);
    void wyswietl_stan(gra &GRA);
    void wyswietl_wygranego(char wygrany);
    void dodaj_ruch_kompa(c_ruch ruch){tablica[ruch.w][ruch.k].setTexture(kolko); oknoGry.display();};
    sf::RenderWindow &zwrocOkno(){return oknoGry;};
};


#endif // GUI_H_INCLUDED
