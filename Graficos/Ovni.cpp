#include "Ovni.hpp"
#include <iostream>

std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(-3.14159,3.14159);

Ovni::Ovni() :
        Circular({0,0}, 15){
    estado = MUERTO;
    if (!bufferSonidoDisparo.loadFromFile("Recursos/Sonido/fire.wav")){
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/fire.wav\"");
    }
    if (!bufferSonidoOvni.loadFromFile("Recursos/Sonido/saucerBig.wav")){
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/thrust.wav\"");
    }

    reproductorDeSonidoOvni.setBuffer(bufferSonidoOvni);
    reproductorDeSonidoDisparos.setBuffer(bufferSonidoDisparo);

    num_disparos = 0;

    poligono.setPrimitiveType(sf::LineStrip);
    poligono.resize(12);
    poligono[0].position = {-1.0f,0.0f};
    poligono[1].position = {1.0f,0.0f};
    poligono[2].position = {0.6f,-0.4f};
    poligono[3].position = {-0.6f,-0.4f};
    poligono[4].position = {-1.0f,0.0f};
    poligono[5].position = {-0.6f,0.4f};
    poligono[6].position = {0.6f,0.4f};
    poligono[7].position = {1.0f,0.0f};
    poligono[8].position = {0.6f,-0.4f};
    poligono[9].position = {0.4f,-0.8f};
    poligono[10].position = {-0.4f,-0.8f};
    poligono[11].position = {-0.6f,-0.4f};
}

Ovni::~Ovni(){}

float Ovni::getDireccion() {
    return direccion;
}

sf::Vector2f Ovni::getVelocidad() {
    return velocidad;
}

int Ovni::getPuntuacion() const {
    return 1000;
}

void Ovni::disparar() {
    if(estado==VIVO) {
        if (num_disparos < MAX_DISPAROS) {
            disparos[num_disparos] = Disparo(posicion, direccion);
            disparos[num_disparos].setDireccion(distribution(generator));
            num_disparos++;
        }
        reproductorDeSonidoDisparos.play();
    }
}

void Ovni::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if(estado == VIVO) {
        sf::Transform t;
        t.translate(posicion).scale({radio, radio});
        target.draw(poligono, t);
        sf::CircleShape c;
        c.setRadius(radio);
        c.setOrigin(radio,radio);
        c.setPosition(posicion);
        c.setFillColor(sf::Color::Green);
        target.draw(c);
    }else if(estado == EXP1) {
        sf::CircleShape c;
        c.setRadius(radio);
        c.setOrigin(radio,radio);
        c.setPosition(posicion);
        c.setFillColor(sf::Color::White);
        target.draw(c);
    }else if(estado == EXP2) {
        sf::CircleShape c;
        c.setRadius(radio);
        c.setOrigin(radio,radio);
        c.setPosition(posicion);
        c.setFillColor(sf::Color::Yellow);
        target.draw(c);
    }else if(estado == EXP3){
        sf::CircleShape c;
        c.setRadius(radio);
        c.setOrigin(radio,radio);
        c.setPosition(posicion);
        c.setFillColor(sf::Color::Red);
        target.draw(c);
    }

    for (int i = 0; i < num_disparos; i++) {
        target.draw(disparos[i]);
    }
}

void Ovni::mover(sf::Vector2u limites, std::vector<Asteroide> v, Triangular &n) {
    if(estado == VIVO) {
        std::uniform_real_distribution<float> distributionGirar(0, 1);
        if (distributionGirar(generator) < 0.01) {
            direccion = distribution(generator);
        }
        posicion.x += VELOCIDAD * cos(direccion);
        if (posicion.x - 1 >= limites.x) {
            posicion.x -= limites.x;
        } else if (posicion.x + 1 <= 0.0) {
            posicion.x += limites.x;
        }

        posicion.y += VELOCIDAD * sin(direccion);
        if (posicion.y - 1 >= limites.y) {
            posicion.y -= limites.y;
        } else if (posicion.y + 1 <= 0.0) {
            posicion.y += limites.y;
        }
    }

    if(num_disparos < 2) {
        disparar();
    }

    //Mover los disparos
    for(int i=0 ; i<num_disparos ; i++){
        disparos[i].mover(limites);

        if(disparos[i].comprobarAlcance()){
            recuperarDisparo(i);
            i--;
            continue;
        }

        //Se comprueba el impacto de los disparos
        if (disparos[i].comprobarColision(n)) {
            recuperarDisparo(i);
            i--;
            n.cambiarEstado(DESTRUIDA,{0,0});
            continue;
        }

        for (auto ast = v.begin(); ast != v.end() && num_disparos>0; ++ast) {
            if(comprobarColision(*ast)){
                cambiarEstado(EXP1,{0,0});
            }

            //Se comprueba el impacto de los disparos
            for (int j = 0; j < num_disparos; j++) {
                if (disparos[j].comprobarColision(*ast)) {
                    recuperarDisparo(j);
                    j--;
                    //Destruir asteroide, dividirlo o lo que sea....
                    continue;
                }
            }
        }
    }
}

void Ovni::recuperarDisparo(int d){
    for(int i=d; i<num_disparos-1 ; i++){
        disparos[i] = disparos[i+1];
    }
    num_disparos--;
}

bool Ovni::comprobarColision(Circular& c) {
    if(colisionCirculos(posicion, radio, c.posicion, c.radio)){
        return true;
    }
    return false;
}

bool Ovni::comprobarColision(Triangular& t) {
    if(colisionVerticesCirculo(t.getVertices(),posicion,radio)){
        return true;
    }
    return false;
}

void Ovni::cambiarEstado(int nuevoEstado, sf::Vector2u lim) {
    static int ciclo = 0;
    estado = nuevoEstado;
    switch(nuevoEstado){
        case VIVO:
            ciclo = 0;
            break;
        case EXP1:
            num_disparos=0;
            reproductorDeSonidoOvni.setLoop(false);
            reproductorDeSonidoOvni.stop();
            if(ciclo>=5){
                estado = EXP2;
            }
            break;
        case EXP2:
            if(ciclo>=10){
                estado = EXP3;
            }
            break;
        case EXP3:
            if(ciclo>=15){
                estado = MUERTO;
            }
            break;
        case MUERTO:
            if(rand()%200==0) {
                estado = VIVO;
                std::uniform_real_distribution<float> distributionPos(0,1);
                if(distributionPos(generator) < 0.5) {
                    std::uniform_real_distribution<float> distributionY(0,lim.y);
                    posicion = sf::Vector2f(30.0f,distributionY(generator));
                } else {
                    std::uniform_real_distribution<float> distributionX(0,lim.x);
                    posicion = sf::Vector2f(distributionX(generator),30.0f);
                }
                direccion = distribution(generator);
                num_disparos = 0;
                reproductorDeSonidoOvni.setLoop(true);
                reproductorDeSonidoOvni.play();
            }
            break;
    }
    ciclo++;
}