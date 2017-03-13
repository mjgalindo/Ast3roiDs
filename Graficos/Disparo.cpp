#include "Disparo.hpp"
#include <iostream>

//Constructores
Disparo::Disparo(){}

Disparo::Disparo(sf::Vector2f pos_inicial, float d){

    direccion = d;

    poligono.setPrimitiveType(sf::LineStrip);
    poligono.resize(2);
    poligono[0].position = {1.0,0.0};
    poligono[1].position = {-1.0,0.0};

    //Posicion de la nave
    posicion = pos_inicial;
    distancia = 0;
}

//Destructor
Disparo::~Disparo(){}

//Setters
void Disparo::setPuntos(sf::Vector2f ps[2]){
    poligono[0].position = ps[0];
    poligono[1].position = ps[1];
}

void Disparo::setDireccion(float dir){
    direccion = dir;
}

void Disparo::setPosicion(sf::Vector2f pos){
    posicion = pos;
}

//Getters
sf::VertexArray* Disparo::getPuntos(){
    return &poligono;
}

float Disparo::getDireccion(){
    return direccion;
}

sf::Vector2f Disparo::getPosicion(){
    return posicion;
}

//Dibujo
void Disparo::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    sf::Transform t;
    t.rotate(direccion* (180.0/3.14), posicion).translate(posicion).scale({(float)TAMANO, (float)TAMANO});

    target.draw(poligono, t);

}

//Otros
void Disparo::mover(sf::Vector2u limites) {
    //Mover la nave
    posicion.x += VELOCIDAD*cos(direccion);
    if (posicion.x - 1 >= limites.x) {
        posicion.x -= limites.x;
    } else if (posicion.x + 1 <= 0.0) {
        posicion.x += limites.x;
    }

    posicion.y += VELOCIDAD*sin(direccion);
    if (posicion.y - 1 >= limites.y) {
        posicion.y -= limites.y;
    } else if (posicion.y + 1 <= 0.0) {
        posicion.y += limites.y;
    }

    distancia += VELOCIDAD;
}

bool Disparo::comprobarAlcance(){
    if(distancia>=ALCANCE){
        return true;
    }
    else{
        return false;
    }
}

bool Disparo::comprobarColision(Circular& c) {
    sf::VertexArray poligono_real = poligono;

    sf::Transform t;
    t.rotate(direccion* (180.0/3.14), posicion).translate(posicion).scale({(float)TAMANO, (float)TAMANO});

    poligono_real[0].position = t.transformPoint(poligono[0].position);
    poligono_real[1].position = t.transformPoint(poligono[1].position);

    return colisionVerticesCirculo(poligono_real,c.getPosicion(),c.getRadio());
}

bool Disparo::comprobarColision(Triangular &tri) {
    sf::VertexArray triangulo = tri.getTriangulo();
    sf::VertexArray poligono_real = poligono;

    sf::Transform t;
    t.rotate(direccion* (180.0/3.14), posicion).translate(posicion).scale({(float)TAMANO, (float)TAMANO});

    poligono_real[0].position = t.transformPoint(poligono[0].position);
    poligono_real[1].position = t.transformPoint(poligono[1].position);

    return colisionVerticesTriangulo(poligono_real,triangulo);
}


/*bool Disparo::comprobarColision(Nave& n){
    sf::Vector2f posicion_global(posicion.x+puntos[0].x*TAMANO*cos(direccion)-puntos[0].y*TAMANO*sin(direccion),posicion.y+puntos[0].y*TAMANO*cos(direccion)+puntos[0].x*TAMANO*sin(direccion));
    // (x1-x2)^2 + (y1-y2)^2 < R^2
    if((posicion_global.x-n.getPosicion().x)*(posicion_global.x-n.getPosicion().x)+(posicion_global.y-n.getPosicion().y)*(posicion_global.y-n.getPosicion().y) < n.getRadio()*n.getRadio()) {
        return true;
    }

    posicion_global = sf::Vector2f(posicion.x+puntos[1].x*TAMANO*cos(direccion)-puntos[1].y*TAMANO*sin(direccion),posicion.y+puntos[1].y*TAMANO*cos(direccion)+puntos[1].x*TAMANO*sin(direccion));
    // (x1-x2)^2 + (y1-y2)^2 < R^2
    if((posicion_global.x-n.getPosicion().x)*(posicion_global.x-n.getPosicion().x)+(posicion_global.y-n.getPosicion().y)*(posicion_global.y-n.getPosicion().y) < n.getRadio()*n.getRadio()) {
        return true;
    }

    return false;
}*/
