#include <iostream>
#include "Nave.hpp"

//Constructor
Nave::Nave(sf::Vector2f posicion_inicial){
    if (!bufferSonidoDisparo.loadFromFile("Recursos/Sonido/fire.wav")){
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/fire.wav\"");
    }
    if (!bufferSonidoPropulsion.loadFromFile("Recursos/Sonido/thrust.wav")){
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/thrust.wav\"");
    }
    if (!bufferSonidoDestruccion.loadFromFile("Recursos/Sonido/bangSmall.wav")){
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/bangSmall.wav\"");
    }

    reproductorDeSonidoPropulsion.setBuffer(bufferSonidoPropulsion);
    reproductorDeSonidoDisparos.setBuffer(bufferSonidoDisparo);
    reproductorDeSonidoDestruccion.setBuffer(bufferSonidoDestruccion);


    poligono.setPrimitiveType(sf::LineStrip);
    poligono.resize(5);
    poligono[0].position = {1.0f,0.0f};
    poligono[1].position = {-0.7071067812f,0.7071067812f};
    poligono[2].position = {-0.4f,0.0f};
    poligono[3].position = {-0.7071067812f,-0.7071067812f};
    poligono[4].position = {1.0f,0.0f};

    //fuego.setPrimitiveType(sf::LineStrip);
    fuego.setPointCount(4);
    fuego.setPoint(0, sf::Vector2f(-0.55f, 0.0f));
    fuego.setPoint(1, sf::Vector2f(-0.7f, 0.5f));
    fuego.setPoint(2, sf::Vector2f(-1.0f, 0.0f));
    fuego.setPoint(3, sf::Vector2f(-0.7f, -0.5f));
    //fuego.setPoint(0, sf::Vector2f(-0.55f, 0.0f));

    direccion = (float)-PI/2.0f;

    //Posicion de la nave
    pos_inicial = posicion_inicial;
    posicion = posicion_inicial;

    //Velocidad de la nave
    velocidad = sf::Vector2f(0.0, 0.0);

    estado = REPOSO;

    //Disparos
    num_disparos = 0;
    for(int i=0 ; i<MAX_DISPAROS ; i++){
        disparos[i] = Disparo(sf::Vector2f(0.0, 0.0),0.0);
    }
}

void Nave::reiniciar() {
    direccion = (float)-PI/2.0f;
    //Posicion de la nave
    posicion = pos_inicial;
    //Velocidad de la nave
    velocidad = sf::Vector2f(0.0, 0.0);
}

//Destructor
Nave::~Nave(){}

//Setters
void Nave::setPoligono(sf::Vector2f ps[5]){
    poligono[0].position = ps[0];
    poligono[1].position = ps[1];
    poligono[2].position = ps[2];
    poligono[3].position = ps[3];
    poligono[4].position = ps[4];
}

void Nave::setDireccion(float dir){
    direccion = dir;
}

void Nave::setPosicion(sf::Vector2f pos){
    posicion = pos;
}

void Nave::setVelocidad(sf::Vector2f vel){
    velocidad = vel;
}

//Getters
sf::VertexArray* Nave::getPoligono(){
    return &poligono;
}

float Nave::getDireccion(){
    return direccion;
}

sf::Vector2f Nave::getPosicion(){
    return posicion;
}

sf::Vector2f Nave::getVelocidad(){
    return velocidad;
}

long int Nave::getPuntuacion(){
    return puntuacion;
}

int Nave::getVidas(){
    return vidas;
}

//Dibujo
void Nave::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    switch(estado){
        case REPOSO:
            {
                sf::Transform t;
                t.rotate(direccion* (180.0/3.14), posicion).translate(posicion).scale({(float)TAMANO, (float)TAMANO});

                target.draw(poligono, t);
            }
            break;

        case ACELERANDO:
            {
                sf::Transform t;
                t.rotate(direccion* (180.0/3.14), posicion).translate(posicion).scale({(float)TAMANO, (float)TAMANO});

                target.draw(poligono, t);
                target.draw(fuego, t);
            }
            break;

        case DESTRUIDA:
        {
        }
        break;

        case REAPARECIENDO:
        {
        }
        break;
    }



    //Dibujar los disparos
    for(int i=0 ; i<num_disparos ; i++){
        target.draw(disparos[i]);
    }
}

//Otros
void Nave::disparar(){
    if(estado==REPOSO || estado==ACELERANDO) {
        if (num_disparos < MAX_DISPAROS) {
            sf::Vector2f inicio = poligono[0].position;
            inicio.x = (float) (poligono[0].position.x * TAMANO * cos(direccion) - poligono[0].position.y * TAMANO * sin(direccion));
            inicio.y = (float) (poligono[0].position.y * TAMANO * cos(direccion) + poligono[0].position.x * TAMANO * sin(direccion));
            disparos[num_disparos] = Disparo(posicion + inicio, direccion);
            num_disparos++;
            reproductorDeSonidoDisparos.play();
        }
    }
}

void Nave::rotarIzda(){
    if(estado==REPOSO || estado==ACELERANDO) {
        direccion -= V_ANGULAR;
        if (direccion < 0.0) {
            direccion += 2 * PI;
        }
    }
}

void Nave::rotarDcha(){
    if(estado==REPOSO || estado==ACELERANDO) {
        direccion += V_ANGULAR;
        if (direccion > 2.0 * PI) {
            direccion -= 2 * PI;
        }
    }
}

void Nave::mover(sf::Vector2u limites, std::vector<Asteroide> v, Ovni o){
    if(estado==REPOSO || estado==ACELERANDO) {
        //Mover la nave
        posicion.x += velocidad.x;
        if (posicion.x - 1 >= limites.x) {
            posicion.x -= limites.x;
        } else if (posicion.x + 1 <= 0.0) {
            posicion.x += limites.x;
        }

        posicion.y += velocidad.y;
        if (posicion.y - 1 >= limites.y) {
            posicion.y -= limites.y;
        } else if (posicion.y + 1 <= 0.0) {
            posicion.y += limites.y;
        }

        //Mover los disparos
        for (int i = 0; i < num_disparos; i++) {
            disparos[i].mover(limites);
            if (disparos[i].comprobarAlcance()) {
                if (disparos[i].comprobarAlcance()) {
                    recuperarDisparo(i);
                }
            }
        }

        if(o.getEstado()==VIVO) {
            if(comprobarColision(o)){
                estado = DESTRUIDA;
                o.morir();
                while(num_disparos>0){
                    recuperarDisparo(0);
                }

                puntuacion += o.getPuntuacion();
                vidas--;
            }
        }

        //Se comprueba el impacto de los disparos
        for (int j = 0; j < num_disparos; j++) {
            if (disparos[j].comprobarColision(o)) {
                puntuacion += o.getPuntuacion();
                recuperarDisparo(j);
                j--;

                //Destruir asteroide, dividirlo o lo que sea....
            }
        }

        for (auto a = v.begin(); a != v.end(); ++a) {
            if(comprobarColision(*a)){
                estado = DESTRUIDA;

                while(num_disparos>0){
                    recuperarDisparo(0);
                }

                puntuacion += o.getPuntuacion();
                vidas--;

                //Destruir asteroide, dividirlo o lo que sea....
            }

            //Se comprueba el impacto de los disparos
            for (int j = 0; j < num_disparos; j++) {
                if (disparos[j].comprobarColision(*a)) {
                    puntuacion += a->getPuntuacion();
                    recuperarDisparo(j);
                    j--;

                    //Destruir asteroide, dividirlo o lo que sea....
                }
            }
        }
    }
}

void Nave::recuperarDisparo(int d){
    for(int i=d; i<num_disparos-1 ; i++){
        disparos[i] = disparos[i+1];
    }
    num_disparos--;
}

void Nave::acelerar(){
    if(estado==REPOSO || estado==ACELERANDO) {
        if (velocidad.x * velocidad.x + velocidad.y * velocidad.y < MAX_VELOCIDAD * MAX_VELOCIDAD) {
            velocidad.x += ACELERACION * cos(direccion);
            velocidad.y += ACELERACION * sin(direccion);
        }
        if (reproductorDeSonidoPropulsion.getStatus() == sf::Sound::Status::Stopped) {
            reproductorDeSonidoPropulsion.play();
        }

        estado = ACELERANDO;
    }
}

void Nave::frenar(){
    if(velocidad.x*velocidad.x+velocidad.y*velocidad.y<UMBRAL){
        velocidad.x = 0;
        velocidad.y = 0;
    }
    else{
        velocidad.x *= DECELERACION;
        velocidad.y *= DECELERACION;
    }
}

bool Nave::comprobarColision(Circular& c){
    sf::VertexArray poligono_real;
    poligono_real.setPrimitiveType(sf::LineStrip);
    poligono_real.resize(3);

    sf::Transform t;
    t.rotate(direccion).translate(posicion).scale({TAMANO, TAMANO});

    poligono_real[0].position = t.transformPoint(poligono[0].position);
    poligono_real[1].position = t.transformPoint(poligono[1].position);
    poligono_real[2].position = t.transformPoint(poligono[3].position);

    if(colisionVerticesCirculo(poligono_real,c.posicion, c.radio)){
        return true;
    }

    return false;
}

void Nave::comprobarEstado(){
    static int ciclosDestruida = 0;
    static int ciclosReapareciendo = 0;
    switch(estado) {
        case REPOSO:
            break;
        case ACELERANDO:
            estado = REPOSO;
            break;
        case DESTRUIDA:
            if (ciclosDestruida >= 50) {
                estado = REAPARECIENDO;
                reiniciar();
                ciclosDestruida = 0;
            }
            else{
                ciclosDestruida++;
            }
            break;
        case REAPARECIENDO:
            if (ciclosReapareciendo >= 50) {
                estado = REPOSO;
                ciclosReapareciendo = 0;
            }
            else{
                ciclosReapareciendo++;
            }
            break;
    }
}