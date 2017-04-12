#ifndef AST3ROIDS_MALLA_HPP
#define AST3ROIDS_MALLA_HPP

#include <string>
#include <tiny_obj_loader.h>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include "../Util3D/Transformacion.hpp"
#include "../Util3D/Shader.hpp"
#include "../Util3D/Textura.hpp"

class Elemento3D : public sf::Drawable {
public:
    Elemento3D& predibujado(Camara& camara);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
protected:
    // Constructor protegido para que no se instancie la clase
    Elemento3D(vj::Shader* shader, vj::Textura* textura) : shader(shader), textura(textura){}
    ~Elemento3D();

    Transformacion pos;
    vj::Shader* shader;
    vj::Textura* textura;

    // Estructuras contenedoras del modelo 3D
    enum
    {
        POSITION_VB = 0,
        TEXCOORD_VB = 1,
        NORMAL_VB = 2,
        INDEX_VB = 3,
        NUM_BUFFERS = 4
    };

    GLuint vertexArrayObject;
    GLuint vertexArrayBuffers[NUM_BUFFERS];
    unsigned int numTriangulos;

    std::string fich_obj;
    const std::string ruta_obj = "Recursos/Modelos/";

    void cargaMalla();
};


#endif //AST3ROIDS_MALLA_HPP
