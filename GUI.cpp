#include "GUI.h"


c_GUI::c_GUI(int rozmiar){
    rozmiar_planszy = rozmiar;

    oknoGry.create( sf::VideoMode(800, 800, 32 ), "Kolko i krzyzyk v.0.1", sf::Style::Close);
    kolko.loadFromFile("kolko.png");
    krzyzyk.loadFromFile("krzyzyk.png");
    puste.loadFromFile("puste.png");
    pods.loadFromFile("pods.png");

    tablica = new sf::Sprite* [rozmiar];
    for (int i=0; i<rozmiar; i++){
        tablica[i] = new sf::Sprite[rozmiar];
        for(int j=0; j<rozmiar; j++){
            tablica[i][j] = sf::Sprite(puste);
        }
    }


}

c_GUI::rysuj_plansze(gra &GRA){

    float wielkosc = oknoGry.getSize().x;
    float stosunek = wielkosc/rozmiar_planszy;

    for(int i=0; i<rozmiar_planszy; i++){
        for(int j=0; j<rozmiar_planszy; j++){
            tablica[i][j] = sf::Sprite(puste);
            tablica[i][j].scale(sf::Vector2f(stosunek/puste.getSize().x, stosunek/puste.getSize().x));
            tablica[i][j].scale(skala, skala);
            tablica[i][j].setPosition(sf::Vector2f(stosunek*i + (wielkosc*(1-skala)/rozmiar_planszy/2), stosunek*j + (wielkosc*(1-skala)/rozmiar_planszy/2)));
            oknoGry.draw(tablica[i][j]);
            }
        }

    oknoGry.display();
}


void c_GUI::wyswietl_stan(gra &GRA){
    for(int i=0; i<rozmiar_planszy; i++){
        for(int j=0; j<rozmiar_planszy; j++){
            oknoGry.draw(tablica[i][j]);
            }
        }
}


c_ruch c_GUI::wczytaj_ruch_gracza(gra &GRA){
    sf::Event zdarzenie;
    sf::Vector2i kursor;
    bool nacisnieto = false;
    bool koniec = false;

    while (oknoGry.isOpen() && !koniec){
        nacisnieto = false;
        while (oknoGry.pollEvent(zdarzenie)){
            if (zdarzenie.type == sf::Event::Closed)
                oknoGry.close();
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape )
                oknoGry.close();
            if( zdarzenie.type == sf::Event::MouseMoved)
                kursor =  sf::Mouse::getPosition(oknoGry);
            if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left){
                nacisnieto = true;
                }
        }
        for(int i=0; i<rozmiar_planszy; i++)  //wyroznienie po najechaniu
            for(int j=0; j<rozmiar_planszy; j++)
                if(GRA.zwrocPoleGry()[i][j] == PUSTE_POLE){
                    if(tablica[i][j].getGlobalBounds().contains(kursor.x, kursor.y)){
                        tablica[i][j].setTexture(pods);
                        if(nacisnieto){
                            GRA.dodajRuchGracza(i, j);
                            tablica[i][j].setTexture(krzyzyk);
                            koniec = true;
                        }
                    }
                    else
                        tablica[i][j].setTexture(puste);
                }

        wyswietl_stan(GRA);
        oknoGry.display();
     }
}

void c_GUI::wyswietl_wygranego(char wygrany){
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(oknoGry.getSize().x/10);
    sf::Color kolor(25, 25, 112);
    text.setFillColor(kolor);

    if(wygrany == GRACZ)
        text.setString("WYGRANA");
    else if (wygrany == KOMP)
        text.setString("PRZEGRANA");
    else if (wygrany == 'R')
         text.setString("REMIS");

    sf::FloatRect textRect = text.getLocalBounds();
    text.setPosition(oknoGry.getSize().x/2.0f - textRect.width/2.0f, oknoGry.getSize().y/2.0f - textRect.height*1.5f);
    oknoGry.draw(text);
}
