#ifndef AST3ROIDS_NAVE_HPP
#define AST3ROIDS_NAVE_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Colisiones.hpp"
#include "../Estados.hpp"
#include "Triangular.hpp"
#include "Circular.hpp"
#include "Disparo.hpp"
#include "Asteroide.hpp"
#include "../matematicas.hpp"

#define UMBRAL 0.07

class Nave : public sf::Drawable, public Triangular {
private:
    //Velocidad de giro (radianes por u.t.)
    static constexpr float V_ANGULAR = PI / 30;
    //Aceleracion (pixels por u.t.)
    static constexpr float ACELERACION = 0.3;
    //Deceleracion (porcentaje de velocidad que se conserva)
    static constexpr float DECELERACION = 0.985;
    //Numero maximo de disparos activos
    static const int MAX_DISPAROS = 4;
    //Velocidad maxima
    static const int MAX_VELOCIDAD = 8;

    //Posicion inicial
    sf::Vector2f pos_inicial;

    //Vectores para cuando se destruye
    sf::VertexArray linea0, linea1, linea2, linea3;
    sf::Vector2f posicion0, posicion1, posicion2, posicion3;

    bool recienDestruida = false;

    //Orden: morro, izquierda, derecha y centro
    sf::VertexArray poligono;
    sf::ConvexShape fuego;

    //Velocidad de la nave
    sf::Vector2f velocidad;

    //Numero de disparos
    int num_disparos;
    //Vector de disparos
    Disparo disparos[MAX_DISPAROS];

    //Numero de autoreapariciones de la nave
    int vidas = 5;
    //Puntuacion
    long int *puntuacion;

    // Buffers de los distintos sonidos de una nave
    sf::SoundBuffer bufferSonidoDisparo;
    sf::SoundBuffer bufferSonidoPropulsion;
    sf::SoundBuffer bufferSonidoDestruccion;
    // Reproductores de sonido
    sf::Sound reproductorDeSonidoDisparos;
    sf::Sound reproductorDeSonidoPropulsion;
    sf::Sound reproductorDeSonidoDestruccion;

    void reiniciar();

public:
    //Constructor
    Nave(sf::Vector2f posicion_inicial, long int *p);

    //Destructor
    ~Nave();

    //Setters
    void setPoligono(sf::Vector2f ps[5]);

    void setVelocidad(sf::Vector2f vel);

    void setVidas(int v);

    void setPuntuacion(long int puntuacion);

    //Getters
    sf::VertexArray *getPoligono();

    sf::Vector2f getVelocidad();

    int getVidas();

    long int getPuntuacion();

    //Dibujo
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    //Otros
    void disparar();

    void recuperarDisparo(int d);

    void rotarIzda();

    void rotarDcha();

    void mover(sf::Vector2u limites, std::vector<Asteroide> &v, Circular &o);

    void acelerar();

    void frenar();

    bool comprobarColision(Circular &c);

    virtual void cambiarEstado(int nuevoEstado, sf::Vector2u lim);
};

#endif //AST3ROIDS_NAVE_HPP
