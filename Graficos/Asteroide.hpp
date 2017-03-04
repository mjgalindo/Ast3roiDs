#ifndef AST3ROIDS_ASTEROIDE_HPP
#define AST3ROIDS_ASTEROIDE_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

class Asteroide : public sf::Drawable {

private:
    float direccion;
    float size;
    int version;
    std::array<sf::Vector2f, 12> puntos;
    sf::Vector2f posicion;
    sf::Vector2f velocidad;

public:
    enum Tipo {TIPO_0, TIPO_1, TIPO_2};

    Asteroide(sf::Vector2f posicion_inicial, float dir, sf::Vector2f vel, Tipo tipo, float size);

    ~Asteroide() {};

    std::array<sf::Vector2f, 12> getPuntos();

    float getDireccion();

    sf::Vector2f getPosicion();

    sf::Vector2f getVelocidad();

    void mover(sf::Vector2u limites);

    void explotar() {};

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

};


#endif //AST3ROIDS_ASTEROIDE_HPP