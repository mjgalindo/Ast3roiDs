#ifndef AST3ROIDS_NAVE3D_HPP
#define AST3ROIDS_NAVE3D_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "../Colisiones.hpp"
#include "Elemento3D.hpp"
#include "Asteroide3D.hpp"
#include "Ovni3D.hpp"
#include "Disparo3D.hpp"

class Nave3D : public Elemento3D {
public:
    Nave3D(ControladorSonido *controladorSonido, long int *punt, float limitesMovimiento);

    void actualizar(int nivel, std::vector<Asteroide3D> &asteroides, Ovni3D &ovni, sf::Vector2i movRaton);

    void dibujar(sf::RenderTarget &target, Camara &camara, bool malla = false,
                 sf::RenderStates states = sf::RenderStates::Default) const;

    void disparar();

    void destruir();

    int getVidas();

    void hiperespacio(float radio);

    glm::vec3 velocidad;
    glm::vec3 dirFrente;
    glm::vec3 dirArriba;
    glm::vec3 dirDerecha;

    const glm::vec4 DIRECCION_FRENTE_INICIAL{1.0f, 0.0f, 0.0f, 0.0f};
    const glm::vec4 DIRECCION_ARRIBA_INICIAL{0.0f, 1.0f, 0.0f, 0.0f};
    const glm::vec4 DIRECCION_DERECHA_INICIAL{0.0f, 0.0f, 1.0f, 0.0f};

    static constexpr float RADIO = 7.6f;
    static constexpr float ACELERACION = 0.55f;
    static constexpr float VELOCIDAD_MAX = 15.5f;

    sf::Keyboard::Key teclaAcelerar = sf::Keyboard::Space;

private:
    std::vector<Disparo3D> disparos;
    ControladorSonido *csonido;

    float limiteMovimiento;

    //Numero de autoreapariciones de la nave
    int vidas = 5;
    //Puntuacion
    long int *puntuacion;

    clock_t cooldown;
};


#endif //AST3ROIDS_NAVE3D_HPP
