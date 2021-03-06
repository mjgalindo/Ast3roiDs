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
#include "../ControladorSonido.hpp"

#define UMBRAL 0.07

class Nave : public sf::Drawable, public Triangular {
private:
    //Velocidad de giro (radianes por u.t.)
    static constexpr float V_ANGULAR = (float) (PI / 35);
    //Aceleracion (pixels por u.t.)
    static constexpr float ACELERACION = 0.3;
    //Deceleracion (porcentaje de velocidad que se conserva)
    static constexpr float DECELERACION = 0.985;
    //Numero maximo de disparos activos
    static const int MAX_DISPAROS = 4;
    //Velocidad maxima
    static const int MAX_VELOCIDAD = 4;

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
    sf::Color color;

    sf::Vector2u limites;

    ControladorSonido *cs;
    const ControladorSonido::Sonido
            SonidoDisparo = ControladorSonido::DISPARO,
            SonidoAcelerar = ControladorSonido::ACELERAR,
            SonidoDestruccion = ControladorSonido::EXP_0;

    clock_t cooldown;

    void reiniciar();

public:
    //Constructor
    Nave(sf::Vector2f posicion_inicial, sf::Vector2u limitesPantalla, long int *p, sf::Color color,
         ControladorSonido *cs);


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

    void hiperEspacio();

    void mover(std::vector<Asteroide> &v, Circular &o);

    void acelerar();

    void frenar();

    bool comprobarColision(Circular &c);

    virtual void cambiarEstado(int nuevoEstado);
};

#endif //AST3ROIDS_NAVE_HPP
