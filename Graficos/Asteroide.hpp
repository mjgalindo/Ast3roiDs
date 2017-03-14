#ifndef AST3ROIDS_ASTEROIDE_HPP
#define AST3ROIDS_ASTEROIDE_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

#include "../Estados.hpp"
#include "Circular.hpp"
#include "../matematicas.hpp"

class Asteroide : public sf::Drawable, public Circular {

private:
    float direccion;
    Tipo version;
    sf::VertexArray poligono;
    sf::Vector2f velocidad;

public:

    Asteroide(sf::Vector2f posicion_inicial, float dir, sf::Vector2f vel, Tipo tipo, Tamano tam);

    ~Asteroide() {};

    sf::VertexArray getPuntos();

    float getDireccion();

    sf::Vector2f getVelocidad();

    virtual int getPuntuacion() const;

    void mover(sf::Vector2u limites);

    void explotar() {};

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    //Otros
    virtual void cambiarEstado(int nuevoEstado, sf::Vector2u lim);

    static void nuevosAsteroidesAleatorios(std::vector<Asteroide> &vectorAsteroides, unsigned int numAsteroides,
                                                      sf::Vector2u limitesPantalla) {
        vectorAsteroides.clear();
        for (int i = 0; i < numAsteroides; ++i) {
            vectorAsteroides.push_back(Asteroide(
                    {(float) enteroAleatorio(0, limitesPantalla.x), (float) enteroAleatorio(0, limitesPantalla.y)},
                    anguloAleatorio(), {(float) (valorAleatorio() * cos(anguloAleatorio())),
                                        (float) (valorAleatorio() * sin(anguloAleatorio()))},
                    (Tipo) enteroAleatorio(0, 3), TAM_2));
        }

    }
};


#endif //AST3ROIDS_ASTEROIDE_HPP