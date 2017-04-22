#include <string>
#include <iostream>
#include "Ovni3D.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"
#include "../ControladorSonido.hpp"

using namespace std;
using namespace sf;

Ovni3D::Ovni3D(ControladorSonido *controladorSonido) :
        csonido(controladorSonido),
        Elemento3D(ControladorShaders::getShader(ControladorShaders::SIMPLE),
                   ControladorTexturas::getTextura(ControladorTexturas::VERDE)) {

    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::ASTEROIDE);
    velocidad = {5.0f,  5.0f, 5.0f};
    pos.posicion = {valorAleatorio(-80.0,80.0), valorAleatorio(-80.0,80.0), valorAleatorio(-80.0,80.0)};
    pos.escala = {2.0f, 2.0f, 2.0f};
    pos.rotacion = {0.0f, -PI / 2, 0.0f};
    direccion = glm::vec3(valorAleatorio(-1.0f,1.0f),valorAleatorio(-1.0f,1.0f),valorAleatorio(-1.0f,1.0f));
    velocidad = VELOCIDAD_INICIAL*direccion;
    csonido->reproducir(ControladorSonido::OVNI_GRANDE,false);
}

void Ovni3D::actualizar(std::vector<Asteroide3D> asteroides) {

    pos.posicion += velocidad * (1 / 60.f);

    //Se comprueba la colision con los asteroides
    for(int i=0 ; i<asteroides.size() ; i++){
        if(colisionEsferaEsfera(this->pos.posicion, 7.6f*this->pos.escala.z, asteroides[i].pos.posicion, 1.0f*asteroides[i].pos.escala.y)){
            //COLISION!!!!!!!!!!!!
            //asteroides[i].colisionDetectada();
            asteroides.erase(asteroides.begin()+i);
            i--;
        }
    }

    if(valorAleatorio() <= 0.01) {
        disparar();
    }

    if(valorAleatorio() <= 0.001) {
        direccion = glm::vec3(valorAleatorio(-1.0f,1.0f),valorAleatorio(-1.0f,1.0f),valorAleatorio(-1.0f,1.0f));
        velocidad = VELOCIDAD_INICIAL*direccion;
    }

    // Actualiza los disparos del ovni
    for (int i = 0; i < disparos.size(); i++) {
        disparos[i].actualizar();

        //Se comprueba la colision de los disparos con los asteroides
        for(int j=0 ; j<asteroides.size() ; j++){
            if(colisionPuntoEsfera(disparos[i].pos.posicion,asteroides[j].pos.posicion, 1.0f*asteroides[j].pos.escala.y)){
                //COLISION!!!!!!!!!!!!
                //asteroides[i].colisionDetectada();
                asteroides.erase(asteroides.begin()+j);
                j--;
            }
        }

        if (disparos[i].estado == DESTRUIDO) {
            disparos.erase(disparos.begin() + i);
            i--;
        }
    }
}

void Ovni3D::dibujar(sf::RenderTarget &target, Camara &camara, sf::RenderStates states) const {
    // Dibuja los disparos
    for (const Disparo3D& disparo : disparos)
        disparo.dibujar(target, camara, states);

    predibujado(camara);
    draw(target, states);
}

void Ovni3D::disparar() {
    disparos.emplace_back(direccion, pos.posicion, pos.rotacion);

    csonido->reproducir(ControladorSonido::DISPARO,true);
}