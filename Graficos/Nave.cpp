#include "Nave.hpp"

//Constructor
Nave::Nave(sf::Vector2f posicion_inicial){
    puntos[0] = sf::Vector2f(1.0,0.0);
    puntos[1] = sf::Vector2f(-0.7071067812,0.7071067812);
    puntos[2] = sf::Vector2f(-0.7071067812,-0.7071067812);

    direccion = PI/2.0;

    //Posicion de la nave
    posicion = posicion_inicial;
    //Velocidad de la nave
    sf::Vector2f velocidad = sf::Vector2f(0.0, 0.0);
    //Numero de disparos
    int disparos = 0;
}

//Destructor
Nave::~Nave(){}

//Setters
void Nave::setPuntos(sf::Vector2f ps[3]){
    puntos[0] = ps[0];
    puntos[1] = ps[1];
    puntos[2] = ps[2];
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
sf::Vector2f* Nave::getPuntos(){
    return puntos;
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

//Dibujo
void Nave::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::Vertex linea01[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[0].x*TAMANO*cos(direccion)-puntos[0].y*TAMANO*sin(direccion),posicion.y+puntos[0].y*TAMANO*cos(direccion)+puntos[0].x*TAMANO*sin(direccion)),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[1].x*TAMANO*cos(direccion)-puntos[1].y*TAMANO*sin(direccion),posicion.y+puntos[1].y*TAMANO*cos(direccion)+puntos[1].x*TAMANO*sin(direccion)),sf::Color::White),
    };

    sf::Vertex linea12[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[1].x*TAMANO*cos(direccion)-puntos[1].y*TAMANO*sin(direccion),posicion.y+puntos[1].y*TAMANO*cos(direccion)+puntos[1].x*TAMANO*sin(direccion)),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[2].x*TAMANO*cos(direccion)-puntos[2].y*TAMANO*sin(direccion),posicion.y+puntos[2].y*TAMANO*cos(direccion)+puntos[2].x*TAMANO*sin(direccion)),sf::Color::White),
    };

    sf::Vertex linea20[] = {
            sf::Vertex(sf::Vector2f(posicion.x+puntos[2].x*TAMANO*cos(direccion)-puntos[2].y*TAMANO*sin(direccion),posicion.y+puntos[2].y*TAMANO*cos(direccion)+puntos[2].x*TAMANO*sin(direccion)),sf::Color::White),
            sf::Vertex(sf::Vector2f(posicion.x+puntos[0].x*TAMANO*cos(direccion)-puntos[0].y*TAMANO*sin(direccion),posicion.y+puntos[0].y*TAMANO*cos(direccion)+puntos[0].x*TAMANO*sin(direccion)),sf::Color::White),
    };

    target.draw(linea01, 2, sf::Lines);
    target.draw(linea12, 2, sf::Lines);
    target.draw(linea20, 2, sf::Lines);
}

//Otros
void Nave::disparar(){

}

void Nave::rotarIzda(){
    direccion += V_ANGULAR;
    if(direccion>2.0*PI){
        direccion -= 2*PI;
    }
}

void Nave::rotarDcha(){
    direccion -= V_ANGULAR;
    if(direccion<0.0){
        direccion += 2*PI;
    }
}

void Nave::mover(sf::Vector2u limites){
    posicion.x += velocidad.x;
    if(posicion.x-1>=limites.x){
        posicion.x -= limites.x;
    }
    else if(posicion.x+1<=0.0){
        posicion.x += limites.x;
    }

    posicion.y += velocidad.y;
    if(posicion.y-1>=limites.y){
        posicion.y -= limites.y;
    }
    else if(posicion.y+1<=0.0){
        posicion.y += limites.y;
    }
}

void Nave::acelerar(){
    velocidad.x += ACELERACION*cos(direccion);
    velocidad.y += ACELERACION*sin(direccion);
}

void Nave::frenar(){
    if((velocidad.x<UMBRAL) && (velocidad.x>-UMBRAL)) {
        velocidad.x = 0;
    }
    else{
        velocidad *= DECELERACION;
    }

    if((velocidad.y<UMBRAL) && (velocidad.y>-UMBRAL)) {
        velocidad.y = 0;
    }
    else{
        velocidad.y *= DECELERACION;
    }
}