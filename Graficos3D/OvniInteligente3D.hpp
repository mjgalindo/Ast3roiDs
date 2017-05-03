#ifndef AST3ROIDS_OVNIINTELIGENTE3D_HPP
#define AST3ROIDS_OVNIINTELIGENTE3D_HPP

#include "Ovni3D.hpp"

class OvniInteligente3D : public Ovni3D {

    public:
        OvniInteligente3D(ControladorSonido *controladorSonido, float limitesMovimiento);

        void actualizar(int nivel, std::vector<Asteroide3D> &asteroides, Elemento3D &nave);

        void disparar(Elemento3D nave);

        glm::vec3 direccionSegura(glm::vec3 posicion, std::vector<Asteroide3D> v);

        int getPuntuacion() const;

    private:
        std::string fichero = "Recursos/IA/disparo3D.nnet";
};


#endif //AST3ROIDS_OVNIINTELIGENTE3D_HPP
