#ifndef AST3ROIDS_DISPARO_HPP
#define AST3ROIDS_DISPARO_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

#include "Triangular.hpp"
#include "Circular.hpp"
#include "Asteroide.hpp"
#include "../Colisiones.hpp"

class Disparo : public sf::Drawable {
private:
    //Tamano del disparo en pixeles
    static constexpr float TAMANO = 2.5f;
    //Distancia maxima a la que llega un disparo
    static constexpr float ALCANCE = 600.0f;
    //Velocidad del disparo (total)
    static constexpr float VELOCIDAD = 13.0f;

    //Orden: superior, inferior
    sf::VertexArray poligono;
    //Direccion del disparo
    float direccion;
    //Posicion del disparo
    sf::Vector2f posicion;
    //Distancia recorrida
    float distancia;

    sf::Clock reloj;

public:
    //Constructor
    Disparo();

    Disparo(sf::Vector2f pos_inicial, float d);

    //Destructor
    ~Disparo();

    //Setters
    void setPuntos(sf::Vector2f ps[2]);

    void setDireccion(float dir);

    void setPosicion(sf::Vector2f pos);

    //Getters
    sf::VertexArray *getPuntos();

    float getDireccion();

    sf::Vector2f getPosicion();

    //Dibujo
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    //Otros
    void mover(sf::Vector2u limites);

    bool comprobarAlcance();

    bool comprobarColision(Circular &c);

    bool comprobarColision(Triangular &tri);
};

#endif //AST3ROIDS_DISPARO_HPP
