#ifndef AST3ROIDS_NAVE3D_HPP
#define AST3ROIDS_NAVE3D_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "../Colisiones.hpp"
#include "Elemento3D.hpp"
#include "Asteroide3D.hpp"
#include "Disparo3D.hpp"

class Nave3D : public Elemento3D {
public:
    Nave3D(ControladorSonido *controladorSonido, long int *punt, float limitesMovimiento);

    void actualizar(std::vector<Asteroide3D> &asteroides, sf::Vector2i movRaton);

    void dibujar(sf::RenderTarget &target, Camara &camara, sf::RenderStates states = sf::RenderStates::Default) const;

    void disparar();

    void destruida();

    int getVidas();

    const float VELOCIDAD_MAX = 0.5f;

    glm::vec3 velocidad;
    glm::vec3 dirFrente;
    glm::vec3 dirArriba;
    glm::vec3 dirDerecha;

    const glm::vec4 DIRECCION_FRENTE_INICIAL{1.0f, 0.0f, 0.0f, 0.0f};
    const glm::vec4 DIRECCION_ARRIBA_INICIAL{0.0f, 1.0f, 0.0f, 0.0f};
    const glm::vec4 DIRECCION_DERECHA_INICIAL{0.0f, 0.0f, 1.0f, 0.0f};

private:
    sf::Vector2i ultimaPosicionRaton;
    std::vector<Disparo3D> disparos;
    ControladorSonido *csonido;

    float limiteMovimiento;

    //Numero de autoreapariciones de la nave
    int vidas = 5;
    //Puntuacion
    long int *puntuacion;
};


#endif //AST3ROIDS_NAVE3D_HPP
