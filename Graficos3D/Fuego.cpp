#include "Fuego.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"
using namespace std;
using namespace sf;

Fuego::Fuego(): Elemento3D(ControladorShaders::getShader(ControladorShaders::BRILLO),
                           ControladorTexturas::getTextura(ControladorTexturas::FUEGO)){
    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::FUEGO);

}
void Fuego::actualizar(Posicionamiento posicion){
    pos = posicion;
}
void Fuego::dibujar(sf::RenderTarget &target, Camara &camara, bool rellenar, sf::RenderStates states)const{
    Elemento3D::dibujar(target, camara, rellenar && estado != INVULNERABLE, states);
}
