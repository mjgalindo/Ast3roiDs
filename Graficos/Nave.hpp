#ifndef AST3ROIDS_NAVE_HPP
#define AST3ROIDS_NAVE_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Colisiones.hpp"
#include "Disparo.hpp"
#include "Asteroide.hpp"
#include "Ovni.hpp"

#define PI 3.14159265358979323846
#define UMBRAL 0.15

enum EstadoNave { REPOSO , ACELERANDO , DESTRUIDA, REAPARECIENDO };

class Nave : public sf::Drawable {
    private:
        //Tamano de la nave en pixeles
        static constexpr float TAMANO = 20;
        //Velocidad de giro (radianes por u.t.)
        static constexpr float V_ANGULAR = PI/30;
        //Aceleracion (pixels por u.t.)
        static constexpr float ACELERACION = 0.4;
        //Deceleracion (porcentaje de velocidad que se conserva)
        static constexpr float DECELERACION = 0.993;
        //Numero maximo de disparos activos
        static const int MAX_DISPAROS = 4;
        //Velocidad maxima
        static const int MAX_VELOCIDAD = 7;

        //Posicion inicial
        sf::Vector2f pos_inicial;

        //Orden: morro, izquierda, derecha y centro
        sf::VertexArray poligono;
        sf::ConvexShape fuego;
        //Direccion de la nave
        float direccion;
        //Posicion de la nave
        sf::Vector2f posicion;
        //Velocidad de la nave
        sf::Vector2f velocidad;

        //Numero de disparos
        int num_disparos;
        //Vector de disparos
        Disparo disparos[MAX_DISPAROS];

        //Numero de autoreapariciones de la nave
        int vidas = 5;
        //Puntuacion
        long int puntuacion = 0;

        EstadoNave estado;

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
        Nave(sf::Vector2f posicion_inicial);

        //Destructor
        ~Nave();

        //Setters
        void setPoligono(sf::Vector2f ps[5]);
        void setDireccion(float dir);
        void setPosicion(sf::Vector2f pos);
        void setVelocidad(sf::Vector2f vel);
        void setVidas(int v);
        void setPuntuacion(long int puntuacion);

        //Getters
        sf::VertexArray* getPoligono();
        float getDireccion();
        sf::Vector2f getPosicion();
        sf::Vector2f getVelocidad();
        int getVidas();
        long int getPuntuacion();

        //Dibujo
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        //Otros
        void disparar();
        void recuperarDisparo(int d);
        void rotarIzda();
        void rotarDcha();
        void mover(sf::Vector2u limites, std::vector<Asteroide> v, Ovni o);
        void acelerar();
        void frenar();

        bool comprobarColision(Circular& c);
        void comprobarEstado();
};

#endif //AST3ROIDS_NAVE_HPP
