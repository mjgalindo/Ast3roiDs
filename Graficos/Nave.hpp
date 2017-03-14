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

#define PI 3.14159265358979323846
#define UMBRAL 0.15

class Nave : public sf::Drawable, public Triangular {
    private:
        //Velocidad de giro (radianes por u.t.)
        static constexpr float V_ANGULAR = PI/30;
        //Aceleracion (pixels por u.t.)
        static constexpr float ACELERACION = 0.4;
        //Deceleracion (porcentaje de velocidad que se conserva)
        static constexpr float DECELERACION = 0.987;
        //Numero maximo de disparos activos
        static const int MAX_DISPAROS = 4;
        //Velocidad maxima
        static const int MAX_VELOCIDAD = 7;

        //Posicion inicial
        sf::Vector2f pos_inicial;

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
        long int puntuacion = 0;

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
        void setVelocidad(sf::Vector2f vel);
        void setVidas(int v);
        void setPuntuacion(long int puntuacion);

        //Getters
        sf::VertexArray* getPoligono();
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
        void mover(sf::Vector2u limites, std::vector<Asteroide> &v, Circular &o);
        void acelerar();
        void frenar();

        bool comprobarColision(Circular& c);
        virtual void cambiarEstado(int nuevoEstado, sf::Vector2u lim);
};

#endif //AST3ROIDS_NAVE_HPP
