//
// Created by Jorge on 05/03/2017.
//

#include "Ovni.hpp"

std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(-3.14159,3.14159);

Ovni::Ovni(sf::Vector2u limites) {
    if (!bufferSonidoDisparo.loadFromFile("Recursos/Sonido/fire.wav")){
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/fire.wav\"");
    }
    if (!bufferSonidoOvni.loadFromFile("Recursos/Sonido/saucerBig.wav")){
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/thrust.wav\"");
    }

    reproductorDeSonidoOvni.setBuffer(bufferSonidoOvni);
    reproductorDeSonidoDisparos.setBuffer(bufferSonidoDisparo);

    std::uniform_real_distribution<float> distributionPos(0,1);
    if(distributionPos(generator) < 0.5) {
        std::uniform_real_distribution<float> distributionY(0,limites.y);
        posicion = sf::Vector2f(0.0f,distributionY(generator));
    } else {
        std::uniform_real_distribution<float> distributionX(0,limites.x);
        posicion = sf::Vector2f(distributionX(generator),0.0f);
    }
    puntos[0] = sf::Vector2f(-1.0f,0.0f);
    puntos[1] = sf::Vector2f(1.0f,0.0f);
    puntos[2] = sf::Vector2f(-0.6f,-0.4f);
    puntos[3] = sf::Vector2f(0.6f,-0.4f);
    puntos[4] = sf::Vector2f(-0.6f,0.4f);
    puntos[5] = sf::Vector2f(0.6f,0.4f);
    puntos[6] = sf::Vector2f(-0.4f,-0.8f);
    puntos[7] = sf::Vector2f(0.4f,-0.8f);
    direccion = distribution(generator);
    num_disparos = 0;
}

Ovni::~Ovni(){}

float Ovni::getDireccion() {
    return direccion;
}

sf::Vector2f Ovni::getPosicion() {
    return posicion;
}

sf::Vector2f Ovni::getVelocidad() {
    return velocidad;
}

void Ovni::disparar() {
    if(num_disparos<MAX_DISPAROS) {
        disparos[num_disparos] = Disparo(posicion);
        disparos[num_disparos].setDireccion(distribution(generator));
        num_disparos++;
        reproductorDeSonidoDisparos.play();
    }
}

void Ovni::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::Vertex linea01[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[0].x*TAMANO,posicion.y+puntos[0].y*TAMANO),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[1].x*TAMANO,posicion.y+puntos[1].y*TAMANO),sf::Color::White)
    };
    sf::Vertex linea02[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[0].x*TAMANO,posicion.y+puntos[0].y*TAMANO),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[2].x*TAMANO,posicion.y+puntos[2].y*TAMANO),sf::Color::White)
    };
    sf::Vertex linea13[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[1].x*TAMANO,posicion.y+puntos[1].y*TAMANO),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[3].x*TAMANO,posicion.y+puntos[3].y*TAMANO),sf::Color::White)
    };
    sf::Vertex linea23[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[2].x*TAMANO,posicion.y+puntos[2].y*TAMANO),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[3].x*TAMANO,posicion.y+puntos[3].y*TAMANO),sf::Color::White)
    };
    sf::Vertex linea04[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[0].x*TAMANO,posicion.y+puntos[0].y*TAMANO),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[4].x*TAMANO,posicion.y+puntos[4].y*TAMANO),sf::Color::White)
    };
    sf::Vertex linea15[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[1].x*TAMANO,posicion.y+puntos[1].y*TAMANO),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[5].x*TAMANO,posicion.y+puntos[5].y*TAMANO),sf::Color::White)
    };
    sf::Vertex linea45[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[4].x*TAMANO,posicion.y+puntos[4].y*TAMANO),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[5].x*TAMANO,posicion.y+puntos[5].y*TAMANO),sf::Color::White)
    };
    sf::Vertex linea26[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[2].x*TAMANO,posicion.y+puntos[2].y*TAMANO),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[6].x*TAMANO,posicion.y+puntos[6].y*TAMANO),sf::Color::White)
    };
    sf::Vertex linea37[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[3].x*TAMANO,posicion.y+puntos[3].y*TAMANO),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[7].x*TAMANO,posicion.y+puntos[7].y*TAMANO),sf::Color::White)
    };
    sf::Vertex linea67[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[6].x*TAMANO,posicion.y+puntos[6].y*TAMANO),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[7].x*TAMANO,posicion.y+puntos[7].y*TAMANO),sf::Color::White)
    };
    target.draw(linea01,2,sf::Lines);
    target.draw(linea02,2,sf::Lines);
    target.draw(linea13,2,sf::Lines);
    target.draw(linea23,2,sf::Lines);
    target.draw(linea04,2,sf::Lines);
    target.draw(linea15,2,sf::Lines);
    target.draw(linea45,2,sf::Lines);
    target.draw(linea26,2,sf::Lines);
    target.draw(linea37,2,sf::Lines);
    target.draw(linea67,2,sf::Lines);
    for(int i=0 ; i<num_disparos ; i++){
        target.draw(disparos[i]);
    }
}

void Ovni::mover(sf::Vector2u limites) {
    std::uniform_real_distribution<float> distributionGirar(0,1);
    if(distributionGirar(generator) < 0.01) {
        direccion = distribution(generator);
    }
    posicion.x += VELOCIDAD*cos(direccion);
    if(posicion.x-1>=limites.x){
        posicion.x -= limites.x;
    }
    else if(posicion.x+1<=0.0){
        posicion.x += limites.x;
    }

    posicion.y += VELOCIDAD*sin(direccion);
    if(posicion.y-1>=limites.y){
        posicion.y -= limites.y;
    }
    else if(posicion.y+1<=0.0){
        posicion.y += limites.y;
    }

    //Mover los disparos
    for(int i=0 ; i<num_disparos ; i++){
        disparos[i].mover(limites);
        if(disparos[i].comprobarAlcance()){
                recuperarDisparo(i);
        }
    }

    if(num_disparos < 2) {
        disparar();
    }
    reproductorDeSonidoOvni.play();
}



void Ovni::recuperarDisparo(int d){
    for(int i=d; i<num_disparos-1 ; i++){
        disparos[i] = disparos[i+1];
    }
    num_disparos--;
}