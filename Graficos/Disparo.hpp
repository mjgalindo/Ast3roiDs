#ifndef AST3ROIDS_DISPARO_HPP
#define AST3ROIDS_DISPARO_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
class Disparo : public sf::Drawable {

private:
    sf::Vector2f posicion;
    sf::Vector2f posicionInicial;
    float direccion;
    sf::Vector2f velocidad;
    float distanciaMax;
    float distanciaRecorrida;

public:
    Disparo();
    Disparo(float, float, float);
    void mover(sf::Vector2u limites);
    bool terminado();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //AST3ROIDS_DISPARO_HPP
