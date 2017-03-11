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
    radio = 30;


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

    direccion = distribution(generator);
    num_disparos = 0;
    reproductorDeSonidoOvni.setLoop(true);
    reproductorDeSonidoOvni.play();
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
    if(num_disparos<MAX_DISPAROS) {
        disparos[num_disparos] = Disparo(posicion,direccion);
        disparos[num_disparos].setDireccion(distribution(generator));
        num_disparos++;
    }
    reproductorDeSonidoDisparos.play();
}

void Ovni::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::Transform t;
    t.translate(posicion).scale(radio,radio);
    target.draw(poligono,t);
    for(int i=0 ; i<num_disparos ; i++){
        target.draw(disparos[i]);
    }
}

void Ovni::mover(sf::Vector2u limites, std::vector<Asteroide> v) {
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
            i--;
        }
    }

    if(num_disparos < 2) {
        disparar();
    }

    for (auto ast = v.begin(); ast != v.end(); ++ast) {
        if(comprobarColision(*ast)){
            //EL OVNI SE DESTRUYE???
        }

        //Se comprueba el impacto de los disparos
        for (int j = 0; j < num_disparos; j++) {
            if (disparos[j].comprobarColision(*ast)) {
                recuperarDisparo(j);
                j--;

                //Destruir asteroide, dividirlo o lo que sea....
            }
        }
    }


    reproductorDeSonidoOvni.play();
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