#include "Fuego.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"
using namespace std;
using namespace sf;

Fuego::Fuego(): Elemento3D(ControladorShaders::getShader(ControladorShaders::BRILLO),
                           ControladorTexturas::getTextura(ControladorTexturas::FUEGO)){
    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::FUEGO);
    contador = 0.0f;
}
void Fuego::actualizar(Posicionamiento posicion){
    contador += 0.1;
    float vibracion = abs(sin(contador)/5);
    pos.posicion = posicion.posicion;
    pos.rotacion = posicion.rotacion;
    glm::vec3 e = {posicion.escala.x, posicion.escala.y-vibracion, posicion.escala.z-vibracion};
    pos.escala = e;
}
void Fuego::dibujar(sf::RenderTarget &target, Camara &camara, bool rellenar, sf::RenderStates states)const{
    Elemento3D::dibujar(target, camara, rellenar && estado != INVULNERABLE, states);
}
