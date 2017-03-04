#include "Asteroide.hpp"

Asteroide::Asteroide(sf::Vector2f posicion_inicial, float dir, sf::Vector2f vel, Tipo tipo, float size) {
    posicion = posicion_inicial;
    direccion = dir;
    velocidad = vel;
    this->size = size;
    version = tipo;
    switch (tipo) {
        case TIPO_0:
            puntos[0] = sf::Vector2f(-12.f, -5.7f);
            puntos[1] = sf::Vector2f(-12.3f, -3.7f);
            puntos[2] = sf::Vector2f(-4.7f, 8.5f);
            puntos[3] = sf::Vector2f(4.3f, 8.7f);
            puntos[4] = sf::Vector2f(13.f, 3.3f);
            puntos[5] = sf::Vector2f(9.7f, -1.f);
            puntos[6] = sf::Vector2f(9.5f, -8.3f);
            puntos[7] = sf::Vector2f(6.3f, -13.5f);
            puntos[8] = sf::Vector2f(0.5f, -7.7f);
            puntos[9] = sf::Vector2f(-5.7f, -13.0f);
            break;
        case TIPO_1:
            puntos[0] = sf::Vector2f(-6.f, -11.2f);
            puntos[1] = sf::Vector2f(-2.5f, -5.5f);
            puntos[2] = sf::Vector2f(-11.5f, -5.5f);
            puntos[3] = sf::Vector2f(-11.8f, 3.0f);
            puntos[4] = sf::Vector2f(-3.8f, 12.0f);
            puntos[5] = sf::Vector2f(4.0f, 8.8f);
            puntos[6] = sf::Vector2f(6.8f, 12.5f);
            puntos[7] = sf::Vector2f(12.2f, 5.5f);
            puntos[8] = sf::Vector2f(5.2f, 1.f);
            puntos[9] = sf::Vector2f(13.2f, -2.0f);
            puntos[10] = sf::Vector2f(16.2f, -5.5f);
            puntos[11] = sf::Vector2f(4.2f, -10.8f);
            break;
        case TIPO_2:
            puntos[0] = sf::Vector2f(-4.6f, -11.2f);
            puntos[1] = sf::Vector2f(-11.0f, -5.4f);
            puntos[2] = sf::Vector2f(-7.6f, -1.0f);
            puntos[3] = sf::Vector2f(-10.8f, 5.8f);
            puntos[4] = sf::Vector2f(-4.8f, 11.8f);
            puntos[5] = sf::Vector2f(-1.0f, 8.0f);
            puntos[6] = sf::Vector2f(6.7f, 10.3f);
            puntos[7] = sf::Vector2f(12.7f, 2.6f);
            puntos[8] = sf::Vector2f(7.4f, -2.7f);
            puntos[9] = sf::Vector2f(12.2f, -5.7f);
            puntos[10] = sf::Vector2f(7.0f, -11.0f);
    }
}

//Getters
std::array<sf::Vector2f, 12> Asteroide::getPuntos() {
    return puntos;
}

float Asteroide::getDireccion() {
    return direccion;
}

sf::Vector2f Asteroide::getPosicion() {
    return posicion;
}

sf::Vector2f Asteroide::getVelocidad() {
    return velocidad;
}

void Asteroide::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    sf::Vertex v1 = sf::Vertex(
            sf::Vector2f(
                    (float) (posicion.x + size * puntos[0].x * cos(direccion) - size * puntos[0].y * sin(direccion)),
                    (float) (posicion.y + size * puntos[0].y * cos(direccion) + size * puntos[0].x * sin(direccion))),
            sf::Color::White);
    sf::Vertex v2 = sf::Vertex(
            sf::Vector2f(
                    (float) (posicion.x + size * puntos[1].x * cos(direccion) - size * puntos[1].y * sin(direccion)),
                    (float) (posicion.y + size * puntos[1].y * cos(direccion) + size * puntos[1].x * sin(direccion))),
            sf::Color::White);
    sf::Vertex v3 = sf::Vertex(
            sf::Vector2f(
                    (float) (posicion.x + size * puntos[2].x * cos(direccion) - size * puntos[2].y * sin(direccion)),
                    (float) (posicion.y + size * puntos[2].y * cos(direccion) + size * puntos[2].x * sin(direccion))),
            sf::Color::White);
    sf::Vertex v4 = sf::Vertex(
            sf::Vector2f(
                    (float) (posicion.x + size * puntos[3].x * cos(direccion) - size * puntos[3].y * sin(direccion)),
                    (float) (posicion.y + size * puntos[3].y * cos(direccion) + size * puntos[3].x * sin(direccion))),
            sf::Color::White);
    sf::Vertex v5 = sf::Vertex(
            sf::Vector2f(
                    (float) (posicion.x + size * puntos[4].x * cos(direccion) - size * puntos[4].y * sin(direccion)),
                    (float) (posicion.y + size * puntos[4].y * cos(direccion) + size * puntos[4].x * sin(direccion))),
            sf::Color::White);
    sf::Vertex v6 = sf::Vertex(
            sf::Vector2f(
                    (float) (posicion.x + size * puntos[5].x * cos(direccion) - size * puntos[5].y * sin(direccion)),
                    (float) (posicion.y + size * puntos[5].y * cos(direccion) + size * puntos[5].x * sin(direccion))),
            sf::Color::White);
    sf::Vertex v7 = sf::Vertex(
            sf::Vector2f(
                    (float) (posicion.x + size * puntos[6].x * cos(direccion) - size * puntos[6].y * sin(direccion)),
                    (float) (posicion.y + size * puntos[6].y * cos(direccion) + size * puntos[6].x * sin(direccion))),
            sf::Color::White);
    sf::Vertex v8 = sf::Vertex(
            sf::Vector2f(
                    (float) (posicion.x + size * puntos[7].x * cos(direccion) - size * puntos[7].y * sin(direccion)),
                    (float) (posicion.y + size * puntos[7].y * cos(direccion) + size * puntos[7].x * sin(direccion))),
            sf::Color::White);
    sf::Vertex v9 = sf::Vertex(
            sf::Vector2f(
                    (float) (posicion.x + size * puntos[8].x * cos(direccion) - size * puntos[8].y * sin(direccion)),
                    (float) (posicion.y + size * puntos[8].y * cos(direccion) + size * puntos[8].x * sin(direccion))),
            sf::Color::White);
    sf::Vertex v10 = sf::Vertex(
            sf::Vector2f(
                    (float) (posicion.x + size * puntos[9].x * cos(direccion) - size * puntos[9].y * sin(direccion)),
                    (float) (posicion.y + size * puntos[9].y * cos(direccion) + size * puntos[9].x * sin(direccion))),
            sf::Color::White);

    sf::Vertex linea1[] = {v1, v2};
    sf::Vertex linea2[] = {v2, v3};
    sf::Vertex linea3[] = {v3, v4};
    sf::Vertex linea4[] = {v4, v5};
    sf::Vertex linea5[] = {v5, v6};
    sf::Vertex linea6[] = {v6, v7};
    sf::Vertex linea7[] = {v7, v8};
    sf::Vertex linea8[] = {v8, v9};
    sf::Vertex linea9[] = {v9, v10};

    if (version < 0) {
        sf::Vertex v11 = sf::Vertex(
                sf::Vector2f((float) (posicion.x + size * puntos[10].x * cos(direccion) -
                                      size * puntos[10].y * sin(direccion)),
                             (float) (posicion.y + size * puntos[10].y * cos(direccion) +
                                      size * puntos[10].x * sin(direccion))),
                sf::Color::White);
        if (version == 1) {
            sf::Vertex v12 = sf::Vertex(sf::Vector2f(
                    (float) (posicion.x + size * puntos[11].x * cos(direccion) - size * puntos[11].y * sin(direccion)),
                    (float) (posicion.y + size * puntos[11].y * cos(direccion) + size * puntos[11].x * sin(direccion))),
                                        sf::Color::White);
            sf::Vertex linea11[] = {v11, v12};
            sf::Vertex linea12[] = {v12, v1};

            target.draw(linea11, 2, sf::Lines);
            target.draw(linea12, 2, sf::Lines);
        } else {
            sf::Vertex linea11[] = {v11, v1};

            target.draw(linea11, 2, sf::Lines);
        }
        sf::Vertex linea10[] = {v10, v11};

        target.draw(linea10, 2, sf::Lines);
    } else {
        sf::Vertex linea10[] = {v10, v1};

        target.draw(linea10, 2, sf::Lines);
    }

    target.draw(linea1, 2, sf::Lines);
    target.draw(linea2, 2, sf::Lines);
    target.draw(linea3, 2, sf::Lines);
    target.draw(linea4, 2, sf::Lines);
    target.draw(linea5, 2, sf::Lines);
    target.draw(linea6, 2, sf::Lines);
    target.draw(linea7, 2, sf::Lines);
    target.draw(linea8, 2, sf::Lines);
    target.draw(linea9, 2, sf::Lines);
}

void Asteroide::mover(sf::Vector2u limites) {
    posicion += velocidad;
    if (posicion.x - 1 >= limites.x) {
        posicion.x -= limites.x;
    } else if (posicion.x + 1 <= 0.0) {
        posicion.x += limites.x;
    }
    if (posicion.y - 1 >= limites.y) {
        posicion.y -= limites.y;
    } else if (posicion.y + 1 <= 0.0) {
        posicion.y += limites.y;
    }
}
