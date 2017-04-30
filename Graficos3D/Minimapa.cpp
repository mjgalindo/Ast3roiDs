//
// Created by ALEX on 28/04/2017.
//

#include "Minimapa.hpp"

#include <iostream>

// 2 de los 3 ejes deben ser true y el otro false;
Minimapa::Minimapa(sf::Vector2f pos, sf::Vector2u dimensiones, bool ejeX, bool ejeY, bool ejeZ){
    posicion = pos;
    this->dimensiones = dimensiones;
    this->ejeX = ejeX;
    this->ejeY = ejeY;
    this->ejeZ = ejeZ;

    elementosSet = false;
}

void Minimapa::setElementos3D(Nave3D* n, Ovni3D* o, std::vector<Asteroide3D>* va, float radio){
    nave = n;
    ovni = o;
    asteroides = va;
    this->radio = radio;

    elementosSet = true;
}

void Minimapa::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    if(elementosSet){

        //Borramos la zona donde se va a dibujar el mapa
        sf::CircleShape zonaNegra(dimensiones.x/2.0f);
        zonaNegra.setPosition(posicion);
        zonaNegra.setFillColor(sf::Color(0,100,100,150));

        target.draw(zonaNegra);

        if(ejeX && ejeY){
            sf::CircleShape navecita(dimensiones.x/50.0f);
            navecita.setPosition(posicion.x+(nave->pos.posicion.x+radio)/(2*radio)*dimensiones.x, posicion.y+(nave->pos.posicion.y+radio)/(2*radio)*dimensiones.y);
            navecita.setFillColor(sf::Color::Yellow);

            target.draw(navecita);

            std::vector<Disparo3D> disparos = nave->getDisparos();

            for(unsigned int i=0 ; i<disparos.size() ; i++){
                sf::CircleShape disparito(dimensiones.x / 200.0f);
                disparito.setPosition(posicion.x + (disparos[i].pos.posicion.x + radio) / (2 * radio) * dimensiones.x,
                                     posicion.y + (disparos[i].pos.posicion.y + radio) / (2 * radio) * dimensiones.y);
                disparito.setFillColor(sf::Color::Yellow);

                target.draw(disparito);
            }

            if(!ovni->getEstado()==MUERTO) {
                sf::CircleShape ovnicito(dimensiones.x / 50.0f);
                ovnicito.setPosition(posicion.x + (ovni->pos.posicion.x + radio) / (2 * radio) * dimensiones.x,
                                     posicion.y + (ovni->pos.posicion.y + radio) / (2 * radio) * dimensiones.y);
                ovnicito.setFillColor(sf::Color::Green);

                target.draw(ovnicito);
            }

            for(int i=0 ; i<asteroides->size() ; i++) {

                sf::CircleShape asteroidito(dimensiones.x/50.0f);
                switch((*asteroides)[i].getTamano3D()){
                    case TAM3D_0:
                        asteroidito.setRadius(dimensiones.x/120.0f);
                        break;
                    case TAM3D_1:
                        asteroidito.setRadius(dimensiones.x/80.0f);
                        break;
                    case TAM3D_2:
                        asteroidito.setRadius(dimensiones.x/40.0f);
                        break;
                }
                asteroidito.setPosition(posicion.x+((*asteroides)[i].pos.posicion.x+radio)/(2*radio)*dimensiones.x, posicion.y+((*asteroides)[i].pos.posicion.y+radio)/(2*radio)*dimensiones.y);
                asteroidito.setFillColor(sf::Color::White);

                target.draw(asteroidito);
            }
        }
        else if(ejeY && ejeZ){
            sf::CircleShape navecita(dimensiones.x/50.0f);
            navecita.setPosition(posicion.x+(nave->pos.posicion.y+radio)/(2*radio)*dimensiones.x, posicion.y+(nave->pos.posicion.z+radio)/(2*radio)*dimensiones.y);
            navecita.setFillColor(sf::Color::Yellow);

            target.draw(navecita);

            std::vector<Disparo3D> disparos = nave->getDisparos();

            for(unsigned int i=0 ; i<disparos.size() ; i++){
                sf::CircleShape disparito(dimensiones.x / 200.0f);
                disparito.setPosition(posicion.x + (disparos[i].pos.posicion.y + radio) / (2 * radio) * dimensiones.x,
                                      posicion.y + (disparos[i].pos.posicion.z + radio) / (2 * radio) * dimensiones.y);
                disparito.setFillColor(sf::Color::Yellow);

                target.draw(disparito);
            }

            if(!ovni->getEstado()==MUERTO) {
                sf::CircleShape ovnicito(dimensiones.x / 50.0f);
                ovnicito.setPosition(posicion.x + (ovni->pos.posicion.y + radio) / (2 * radio) * dimensiones.x,
                                     posicion.y + (ovni->pos.posicion.z + radio) / (2 * radio) * dimensiones.y);
                ovnicito.setFillColor(sf::Color::Green);

                target.draw(ovnicito);
            }

            for(int i=0 ; i<asteroides->size() ; i++) {

                sf::CircleShape asteroidito(dimensiones.x/50.0f);
                switch((*asteroides)[i].getTamano3D()){
                    case TAM3D_0:
                        asteroidito.setRadius(dimensiones.x/120.0f);
                        break;
                    case TAM3D_1:
                        asteroidito.setRadius(dimensiones.x/80.0f);
                        break;
                    case TAM3D_2:
                        asteroidito.setRadius(dimensiones.x/40.0f);
                        break;
                }
                asteroidito.setPosition(posicion.x+((*asteroides)[i].pos.posicion.y+radio)/(2*radio)*dimensiones.x, posicion.y+((*asteroides)[i].pos.posicion.z+radio)/(2*radio)*dimensiones.y);
                asteroidito.setFillColor(sf::Color::White);

                target.draw(asteroidito);
            }
        }
        else if(ejeX && ejeZ){
            sf::CircleShape navecita(dimensiones.x/50.0f);
            navecita.setPosition(posicion.x+(nave->pos.posicion.x+radio)/(2*radio)*dimensiones.x, posicion.y+(nave->pos.posicion.z+radio)/(2*radio)*dimensiones.y);
            navecita.setFillColor(sf::Color::Yellow);

            target.draw(navecita);

            std::vector<Disparo3D> disparos = nave->getDisparos();

            for(unsigned int i=0 ; i<disparos.size() ; i++){
                sf::CircleShape disparito(dimensiones.x / 200.0f);
                disparito.setPosition(posicion.x + (disparos[i].pos.posicion.x + radio) / (2 * radio) * dimensiones.x,
                                      posicion.y + (disparos[i].pos.posicion.z + radio) / (2 * radio) * dimensiones.y);
                disparito.setFillColor(sf::Color::Yellow);

                target.draw(disparito);
            }

            if(!ovni->getEstado()==MUERTO) {
                sf::CircleShape ovnicito(dimensiones.x / 50.0f);
                ovnicito.setPosition(posicion.x + (ovni->pos.posicion.x + radio) / (2 * radio) * dimensiones.x,
                                     posicion.y + (ovni->pos.posicion.z + radio) / (2 * radio) * dimensiones.y);
                ovnicito.setFillColor(sf::Color::Green);

                target.draw(ovnicito);
            }

            for(int i=0 ; i<asteroides->size() ; i++) {

                sf::CircleShape asteroidito(dimensiones.x/50.0f);
                switch((*asteroides)[i].getTamano3D()){
                    case TAM3D_0:
                        asteroidito.setRadius(dimensiones.x/120.0f);
                        break;
                    case TAM3D_1:
                        asteroidito.setRadius(dimensiones.x/80.0f);
                        break;
                    case TAM3D_2:
                        asteroidito.setRadius(dimensiones.x/40.0f);
                        break;
                }
                asteroidito.setPosition(posicion.x+((*asteroides)[i].pos.posicion.x+radio)/(2*radio)*dimensiones.x, posicion.y+((*asteroides)[i].pos.posicion.z+radio)/(2*radio)*dimensiones.y);
                asteroidito.setFillColor(sf::Color::White);

                target.draw(asteroidito);
            }
        }
    }
}