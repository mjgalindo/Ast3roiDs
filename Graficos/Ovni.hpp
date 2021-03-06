#ifndef AST3ROIDS_OVNI_HPP
#define AST3ROIDS_OVNI_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../Estados.hpp"
#include "../Colisiones.hpp"
#include "../neural/include/neural/Network.h"
#include "Asteroide.hpp"
#include "Disparo.hpp"

class Ovni : public sf::Drawable, public Circular {

protected:
    static constexpr float VELOCIDAD = 3.0;
    //Numero maximo de disparos activos
    static const int MAX_DISPAROS = 2;
    //Direccion en que se mueve el ovni
    double direccion;

    sf::VertexArray poligono;
    sf::VertexArray punto;
    sf::Vector2f posicion0, posicion1, posicion2, posicion3, posicion4, posicion5, posicion6, posicion7;
    bool recienDestruida = true;

    sf::Vector2f velocidad;

    //Numero de disparos
    int num_disparos;
    //Vector de disparos
    Disparo disparos[MAX_DISPAROS];

    sf::Vector2u limites;
    sf::Color color;

    ControladorSonido *cs;
    const ControladorSonido::Sonido
            SonidoDisparo = ControladorSonido::DISPARO;

    ControladorSonido::Sonido SonidoPresencia, SonidoDestruccion;

    clock_t start;


    std::vector<double> direcciones;

    double ultimaDireccion;

public:

    Ovni(sf::Vector2u limitesPantalla, sf::Color color, ControladorSonido *cs);

    ~Ovni();

    double distancia(sf::Vector2f a, sf::Vector2f b);

    std::vector<Asteroide *> asteroideMasCercano(sf::Vector2f posicion, std::vector<Asteroide> asteroides);

    //Getters
    double getDireccion();

    sf::Vector2f getVelocidad();

    virtual int getPuntuacion() const;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void disparar();

    virtual void mover(std::vector<Asteroide> &astds, Triangular &nave);

    void recuperarDisparo(int d);

    bool comprobarColision(Circular &c);

    virtual void cambiarEstado(int nuevoEstado);

    double network2Radianes(double salida);

    virtual double direccionSegura(sf::CircleShape ovni, sf::Vector2f posicionSegura, std::vector<Asteroide> v);
};


#endif //AST3ROIDS_OVNI_HPP
