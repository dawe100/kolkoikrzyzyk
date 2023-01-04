#include <SFML/Graphics.hpp>

#include "rozgrywka.h"
#include <string>
//#include "minmax.h"

int main()
{
    bool czy_komp_zaczyna = 0, nacisnieto;
    int rozmiar = 2, ilosc_wrzedzie = 2, glebokosc = 4;

    int V_S = 900, V_W = 500;

    sf::Vector2i kursor;
    sf::Event zdarzenie;

    sf::RenderWindow menu(sf::VideoMode(V_S, V_W), "Menu glowne", sf::Style::Close);
    sf::Texture strzalka;
    strzalka.loadFromFile("strzalka.png");
    sf::Sprite strzalki[6];

    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text wyswie[3];
    sf::Text tytul("Kolko i krzyzyk", font, menu.getSize().x/10);
    sf::Text s_rozmiar("Rozmiar planszy", font, menu.getSize().x/40);
    sf::Text s_ile("Ile wygrywa", font, menu.getSize().x/40);
    sf::Text s_kto("Kto zaczyna", font, menu.getSize().x/40);

    double pozycje[] = {V_S*0.07, V_S*0.20, V_S*0.435, V_S*0.565, V_S*0.80, V_S*0.93};


    //modyfikacja tytulu gry i opisow
    tytul.setLetterSpacing(0.4);
    tytul.setFillColor(sf::Color(0, 100, 0));
    tytul.setPosition(menu.getSize().x*0.14f, menu.getSize().y*0.1);

    s_rozmiar.setFillColor(sf::Color(25, 25, 112));
    s_rozmiar.setPosition(menu.getSize().x*0.03, menu.getSize().y*0.4);

    s_ile.setFillColor(sf::Color(25, 25, 112));
    s_ile.setPosition(menu.getSize().x*0.43, menu.getSize().y*0.4);

    s_kto.setFillColor(sf::Color(25, 25, 112));
    s_kto.setPosition(menu.getSize().x*0.78, menu.getSize().y*0.4);


    //utworzenie wyswietlaczy
    for(int i=0; i<3; i++){
        wyswie[i].setFont(font);
        wyswie[i].setLetterSpacing(0.4);
        wyswie[i].setCharacterSize(menu.getSize().x/10);
        sf::Color kolor(25, 25, 112);
        wyswie[i].setFillColor(kolor);
        wyswie[i].setString("2");
        wyswie[i].setPosition((pozycje[i*2] + V_S*0.065/2), menu.getSize().y*0.3);
    }
    for(int i=0; i<3; i++){
        wyswie[i].setFont(font);
        wyswie[i].setCharacterSize(menu.getSize().x/10);
        sf::Color kolor(25, 25, 112);
        wyswie[i].setFillColor(kolor);
        wyswie[i].setString("2");
        wyswie[i].setPosition((pozycje[i*2] + V_S*0.065/2), menu.getSize().y*0.4);
    }



    //utworzenie strzalek
    for(int i=0; i<6; i++){
        strzalki[i].setTexture(strzalka);
        strzalki[i].setOrigin(strzalka.getSize().x/2, strzalka.getSize().y/2);
        strzalki[i].setScale(0.1*menu.getSize().x/strzalka.getSize().x, 0.1*menu.getSize().y/strzalka.getSize().y);
        strzalki[i].setPosition(pozycje[i], menu.getSize().y*0.7);
        strzalki[i].setRotation(180*(!(i%2)));

    }


    // przycisk Graj
    sf::Texture przycisk_graj_t;
    przycisk_graj_t.loadFromFile("graj.png");
    sf::Sprite przycisk_graj(przycisk_graj_t);

    przycisk_graj.setOrigin(przycisk_graj_t.getSize().x/2, przycisk_graj_t.getSize().y/2);
    przycisk_graj.setScale(0.2*menu.getSize().x/przycisk_graj_t.getSize().x, 0.1*menu.getSize().x/przycisk_graj_t.getSize().y);
    przycisk_graj.setPosition(menu.getSize().x/2, menu.getSize().y*0.9);





    while (menu.isOpen()){
        nacisnieto = false;
        while (menu.pollEvent(zdarzenie)){
            if (zdarzenie.type == sf::Event::Closed)
                menu.close();
            if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape )
                menu.close();
            if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left){
                nacisnieto = true;
                kursor =  sf::Mouse::getPosition(menu);
                }
        }
        menu.clear(sf::Color(135, 206, 250));



    //obsluga strzalek
        if(nacisnieto){
            if(strzalki[0].getGlobalBounds().contains(kursor.x, kursor.y) && rozmiar > 2){
                rozmiar--;
                if(ilosc_wrzedzie > 2)
                    ilosc_wrzedzie--;
            }
            if(strzalki[1].getGlobalBounds().contains(kursor.x, kursor.y) && rozmiar < 19){
                rozmiar++;
                ilosc_wrzedzie++;
            }
            if(strzalki[2].getGlobalBounds().contains(kursor.x, kursor.y) && ilosc_wrzedzie > 2)
                ilosc_wrzedzie--;
            if(strzalki[3].getGlobalBounds().contains(kursor.x, kursor.y) && ilosc_wrzedzie < rozmiar)
                ilosc_wrzedzie++;
            if(strzalki[4].getGlobalBounds().contains(kursor.x, kursor.y))
                czy_komp_zaczyna = false;
            if(strzalki[5].getGlobalBounds().contains(kursor.x, kursor.y))
                czy_komp_zaczyna = true;
            if(przycisk_graj.getGlobalBounds().contains(kursor.x, kursor.y)){
                switch(rozmiar){
                    case 2:
                        glebokosc = 4;
                        break;
                    case 3:
                        glebokosc = 9;
                        break;
                    case 4:
                        glebokosc = 7;
                        break;
                    case 5:
                        glebokosc = 5;
                        break;
                    case 6:
                        glebokosc = 4;
                        break;
                    default:
                        glebokosc = 1;
                        break;
                }



//*************************** OTWARCIE OKNA Z GLOWNA ROZGRYWKA *****************************************

    while(rozgrywka(rozmiar, ilosc_wrzedzie, glebokosc, czy_komp_zaczyna));

//******************************************************************************************************
            }
        }


    //obsluga wyswietlaczy
        wyswie[0].setString(std::to_string(rozmiar));
        wyswie[1].setString(std::to_string(ilosc_wrzedzie));
        wyswie[2].setString(czy_komp_zaczyna?"AI":"gracz");

        int offset_r = rozmiar/10;
        int offset_i = ilosc_wrzedzie/10;
        wyswie[0].setPosition((pozycje[0] + V_S*0.065/2) - offset_r*30, wyswie[0].getPosition().y);
        wyswie[1].setPosition((pozycje[2] + V_S*0.065/2) - offset_i*30, wyswie[1].getPosition().y);
        wyswie[2].setPosition((pozycje[4] + V_S*0.065/2) - !czy_komp_zaczyna*90 - 20, wyswie[2].getPosition().y);

    //wyswietlenie obiektow graficznych
        for(int i=0; i<3; i++){

            menu.draw(wyswie[i]);
        }
        for(int i=0; i<6; i++){
            menu.draw(strzalki[i]);
        }
        menu.draw(przycisk_graj);
        menu.draw(tytul);
        menu.draw(s_rozmiar);
        menu.draw(s_kto);
        menu.draw(s_ile);

        menu.display();
    }


return 0;
}
