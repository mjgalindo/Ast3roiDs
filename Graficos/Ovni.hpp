#ifndef AST3ROIDS_OVNI_HPP
#define AST3ROIDS_OVNI_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../Estados.hpp"
#include "../Colisiones.hpp"
#include "Circular.hpp"
#include "Disparo.hpp"
#include "../neural/include/neural/Network.h"

class Ovni : public sf::Drawable, public Circular {

protected:
    static constexpr float VELOCIDAD = 3.0;
    //Numero maximo de disparos activos
    static const int MAX_DISPAROS = 2;
    //Tamaño del ovni
    float radioOvni = 15.0;
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

    // Buffers de los distintos sonidos de un ovni
    sf::SoundBuffer bufferSonidoOvni;
    sf::SoundBuffer bufferSonidoDisparo;

    // Reproductores de sonido
    sf::Sound reproductorDeSonidoDisparos;
    sf::Sound reproductorDeSonidoOvni;

    //Fichero con los pesos de la red
    string fichero = "entrenando.nn";

    clock_t start;
public:
    Ovni(sf::Vector2u limitesPantalla, sf::Color color);

    ~Ovni();

    double distancia(sf::Vector2f a, sf::Vector2f b);

    vector<Asteroide *> asteroideMasCercano(sf::Vector2f posicion, vector<Asteroide> asteroides);

    //Getters
    float getDireccion();

    sf::Vector2f getVelocidad();

    virtual int getPuntuacion() const;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void disparar();

    virtual void mover(std::vector<Asteroide> &v, Triangular &n);

    void recuperarDisparo(int d);

    bool comprobarColision(Circular &c);

    virtual void cambiarEstado(int nuevoEstado);

    double network2Radianes(double salida);
};


#endif //AST3ROIDS_OVNI_HPP
