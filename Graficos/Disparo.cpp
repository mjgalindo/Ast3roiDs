#include "Disparo.hpp"

//Constructores
Disparo::Disparo() {}

Disparo::Disparo(sf::Vector2f pos_inicial, float d, sf::Vector2u limitesPantalla, sf::Color color) {

    direccion = d;

    poligono.setPrimitiveType(sf::LineStrip);
    poligono.resize(2);
    poligono[0].position = {1.0f, 0.0f};
    poligono[1].position = {-1.0f, 0.0f};
    poligono[0].color = color;
    poligono[1].color = color;
    //Posicion de la nave
    posicion = pos_inicial;
    distancia = 0;

    limites = limitesPantalla;
}

//Destructor
Disparo::~Disparo() {}

//Setters
void Disparo::setPuntos(sf::Vector2f ps[2]) {
    poligono[0].position = ps[0];
    poligono[1].position = ps[1];
}

void Disparo::setDireccion(float dir) {
    direccion = dir;
}

void Disparo::setPosicion(sf::Vector2f pos) {
    posicion = pos;
}

//Getters
sf::VertexArray *Disparo::getPuntos() {
    return &poligono;
}

float Disparo::getDireccion() {
    return direccion;
}

sf::Vector2f Disparo::getPosicion() {
    return posicion;
}

//Dibujo
void Disparo::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    sf::Transform t;
    t.rotate((float) (direccion * (180.0 / PI)), posicion).translate(posicion).scale(
            {TAMANO * ratio(limites), TAMANO * ratio(limites)});

    target.draw(poligono, t);
}

//Otros
void Disparo::mover() {
    //Mover la nave
    posicion.x += VELOCIDAD * cos(direccion) * ratio(limites);
    if (posicion.x - 1 >= limites.x) {
        posicion.x -= limites.x;
    } else if (posicion.x + 1 <= 0.0) {
        posicion.x += limites.x;
    }

    posicion.y += VELOCIDAD * sin(direccion) * ratio(limites);
    if (posicion.y - 1 >= limites.y) {
        posicion.y -= limites.y;
    } else if (posicion.y + 1 <= 0.0) {
        posicion.y += limites.y;
    }

    distancia += VELOCIDAD * ratio(limites);
}

bool Disparo::comprobarAlcance() {
    return distancia >= ALCANCE * ratio(limites);
}

bool Disparo::comprobarColision(Circular &c) {
    sf::VertexArray poligono_real = poligono;

    sf::Transform t;
    t.rotate((float) (direccion * (180.0 / PI)), posicion).translate(posicion).scale({(float) TAMANO, (float) TAMANO});

    poligono_real[0].position = t.transformPoint(poligono[0].position);
    poligono_real[1].position = t.transformPoint(poligono[1].position);

    return colisionVerticesCirculo(poligono_real, c.getPosicion(), c.getRadio());
}

bool Disparo::comprobarColision(Triangular &tri) {
    sf::VertexArray triangulo = tri.getTriangulo();
    sf::VertexArray poligono_real = poligono;

    sf::Transform t;
    t.rotate((float) (direccion * (180.0 / PI)), posicion).translate(posicion).scale({(float) TAMANO, (float) TAMANO});

    poligono_real[0].position = t.transformPoint(poligono[0].position);
    poligono_real[1].position = t.transformPoint(poligono[1].position);

    return colisionVerticesTriangulo(poligono_real, triangulo);
}