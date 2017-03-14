#ifndef AST3ROIDS_ASTEROIDE_HPP
#define AST3ROIDS_ASTEROIDE_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

#include "../Estados.hpp"
#include "Circular.hpp"

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
    void gestionarDestruccion(std::vector<Asteroide> &v);
};


#endif //AST3ROIDS_ASTEROIDE_HPP