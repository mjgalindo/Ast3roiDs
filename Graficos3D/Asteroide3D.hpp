#ifndef AST3ROIDS_ASTEROIDE3D_HPP
#define AST3ROIDS_ASTEROIDE3D_HPP

#include "Elemento3D.hpp"
#include "../Estados.hpp"
#include "../ControladorSonido.hpp"
#include "../Estados.hpp"

class Asteroide3D : public Elemento3D {
public:
    Asteroide3D(ControladorSonido *controladorSonido, float limitesMovimiento, Tamano3D tam3D = TAM3D_2);

    Asteroide3D(ControladorSonido *controladorSonido, float limitesMovimiento,
                glm::vec3 posicion, glm::vec3 vel, glm::quat rot, Tipo3D tipo, Tamano3D tam3D);

    void actualizar();

    void dibujar(sf::RenderTarget &target, Camara &camara, sf::RenderStates states = sf::RenderStates::Default) const;

    void colisionDetectada(int nivel, std::vector<Asteroide3D> &asteroides);

    static constexpr float RADIO = 1.0f;

    void dibujarSiCercaAntipoda(glm::vec3 puntoCercano, float distancia, sf::RenderTarget &target, Camara &camara,
                                sf::RenderStates states = sf::RenderStates::Default);

    Tamano3D getTamano3D() { return tamano3D; };

private:
    static constexpr float VELOCIDAD_MAX = 0.2f;
    static constexpr int NUM_FRAGMENTOS = 20;
    static constexpr float TIEMPO_EXPLOSION = 2.0f;

    Tipo3D version;
    Tamano3D tamano3D;

    glm::vec3 velocidad;
    glm::quat velocidadAngular;
    ControladorSonido *csonido;

    float limiteMovimiento;

    std::vector<Asteroide3D> fragmentosExplosion;

    sf::Clock reloj;
};


#endif //AST3ROIDS_ASTEROIDE3D_HPP
