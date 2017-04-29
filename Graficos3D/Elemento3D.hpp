#ifndef AST3ROIDS_MALLA_HPP
#define AST3ROIDS_MALLA_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include "../Util3D/Posicionamiento.hpp"
#include "../Util3D/Shader.hpp"
#include "../Util3D/Textura.hpp"
#include "../Util3D/ControladorModelos.hpp"

class Elemento3D : public sf::Drawable {
public:
    Posicionamiento pos;
    enum Estado3D {
        NORMAL, EXPLOTANDO, DESTRUIDO, INVULNERABLE
    };
    Estado3D estado = NORMAL;

    virtual void dibujar(sf::RenderTarget &target, Camara &camara, bool rellenado = true,
                         sf::RenderStates states = sf::RenderStates::Default) const;

    virtual void destruir();

protected:
    void predibujado(Camara &camara) const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    // Constructor protegido para que no se instancie la clase
    Elemento3D(vj::Shader *shader, vj::Textura *textura) : shader(shader), textura(textura) {}

    vj::Shader *shader;
    vj::Textura *textura;
    Modelo modelo3D;
};

#endif //AST3ROIDS_MALLA_HPP
