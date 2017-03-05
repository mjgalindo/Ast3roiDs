#ifndef AST3ROIDS_ASTEROIDE_HPP
#define AST3ROIDS_ASTEROIDE_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

enum Tipo {TIPO_0, TIPO_1, TIPO_2};
enum Tamano {TAM_0 = 10, TAM_1 = 20, TAM_2 = 40};

class Asteroide : public sf::Drawable {

private:
    float direccion;
    Tamano tamano;
    Tipo version;
    sf::VertexArray poligono;
    sf::Vector2f posicion;
    sf::Vector2f velocidad;

public:


    Asteroide(sf::Vector2f posicion_inicial, float dir, sf::Vector2f vel, Tipo tipo, Tamano tam);

    ~Asteroide() {};

    sf::VertexArray getPuntos();

    float getDireccion();

    sf::Vector2f getPosicion();

    sf::Vector2f getVelocidad();

    float getRadio();

    int getPuntuacion();

    void mover(sf::Vector2u limites);

    void explotar() {};

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

};


#endif //AST3ROIDS_ASTEROIDE_HPP