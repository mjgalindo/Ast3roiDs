#ifndef AST3ROIDS_MALLA_HPP
#define AST3ROIDS_MALLA_HPP

#include <string>
#include <tiny_obj_loader.h>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include "../Util3D/Transformacion.hpp"
#include "../Util3D/Shader.hpp"
#include "../Util3D/Textura.hpp"
#include "../Util3D/ControladorModelos.hpp"

class Elemento3D : public sf::Drawable {
public:
    Elemento3D& predibujado(Camara& camara);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
    // Constructor protegido para que no se instancie la clase
    Elemento3D(vj::Shader* shader, vj::Textura* textura) : shader(shader), textura(textura){}

    Transformacion pos;
    vj::Shader* shader;
    vj::Textura* textura;

    Modelo modelo3D;
};


#endif //AST3ROIDS_MALLA_HPP
