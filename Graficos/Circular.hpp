#ifndef AST3ROIDS_CIRCULAR_HPP
#define AST3ROIDS_CIRCULAR_HPP

#include <SFML/Graphics.hpp>

class Circular {

public:

    sf::Vector2f posicion;
    float radio;
    int estado;

    //Constructores
    Circular();

    Circular(sf::Vector2f p, float r);

    //Destructor
    ~Circular();

    //Setters
    void setPosicion(sf::Vector2f p);

    void setRadio(float r);

    //Getters
    sf::Vector2f getPosicion();

    float getRadio();

    int getEstado();

    virtual int getPuntuacion() const =0;

    //Otros
    virtual void cambiarEstado(int nuevoEstado)=0;
};

#endif //AST3ROIDS_CIRCULAR_HPP
