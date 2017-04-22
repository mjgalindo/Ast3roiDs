#include "Asteroide3D.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"

Asteroide3D::Asteroide3D(ControladorSonido *controladorSonido) : csonido(controladorSonido),
                                                                 Elemento3D(ControladorShaders::getShader(
                                                                         ControladorShaders::SIMPLE),
                                                                            ControladorTexturas::getTextura(
                                                                                    ControladorTexturas::BLANCO)) {
    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::ASTEROIDE);
    velocidad = {0.0f, 0.0f, 0.0f};
    pos.posicion = {
            valorAleatorio(-80, 80),
            valorAleatorio(-80, 80),
            valorAleatorio(-80, 80),
    };
    float escala = valorAleatorio(0.5f, 2.0f);
    pos.escala = {escala, escala, escala};
    pos.rotacion = {PI, 0.0f, 0.0f};

    version = TIPO3D_0;
    tamano3D = TAM3D_2;
}

<<<<<<<<< Temporary merge branch 1
Asteroide3D::Asteroide3D(glm::vec3 pos, glm::vec3 vel, glm::vec3 rot, Tipo3D tipo, Tamano3D tam3D) :
        Elemento3D(ControladorShaders::getShader(ControladorShaders::SIMPLE), ControladorTexturas::getTextura(ControladorTexturas::BLANCO)) {
=========
Asteroide3D::Asteroide3D(ControladorSonido *controladorSonido, glm::vec3 pos, glm::vec3 vel, glm::vec3 rot,
                         glm::vec3 esc) :
        csonido(controladorSonido),
        Elemento3D(ControladorShaders::getShader(ControladorShaders::SIMPLE),
                   ControladorTexturas::getTextura(ControladorTexturas::BLANCO)) {
    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::ASTEROIDE);
>>>>>>>>> Temporary merge branch 2
    velocidad = vel;
    this->pos.posicion = pos;
    this->pos.rotacion = rot;

    version = tipo;
    tamano3D = tam3D;

    switch(version){
        case TIPO3D_0:
        case TIPO3D_1:
        case TIPO3D_2:
        default:
            modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::ASTEROIDE);
    }

    switch(tamano3D){
        case TAM3D_0:
            this->pos.escala = {0.5f , 0.5f , 0.5f};
            break;
        case TAM3D_1:
            this->pos.escala = {1.0f , 1.0f , 1.0f};
            break;
        case TAM3D_2:
            this->pos.escala = {2.0f , 2.0f , 2.0f};
            break;
    }
}

void Asteroide3D::actualizar() {
    pos.posicion += velocidad * (1 / 60.f);
}

<<<<<<<<< Temporary merge branch 1
void Asteroide3D::colisionDetectada(std::vector<Asteroide3D> &asteroides){
    int aleatorio = enteroAleatorio(0,20);
    switch (tamano3D) {
        case TAM3D_0:
            break;
        case TAM3D_1:
            if(aleatorio<2) {
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_0));

            }
            else if(aleatorio<14){
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_0));
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_0));
            }
            else if(aleatorio<18){
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_0));
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_0));
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_0));
            }
            else{
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_0));
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_0));
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_0));
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_0));
            }
            break;
        case TAM3D_2:
            if(aleatorio<2){
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_1));
            }

            else if(aleatorio<14){
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_1));
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_1));
            }
            else if(aleatorio<18){
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_1));
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_1));
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_1));
            }
            else{
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_1));
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_1));
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_1));
                asteroides.push_back(Asteroide3D(this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(),anguloAleatorio(),anguloAleatorio()},(Tipo3D)enteroAleatorio(0,2),TAM3D_1));
            }
            break;
=========
void Asteroide3D::colisionDetectada(std::vector<Asteroide3D> &asteroides) {
    int aleatorio = enteroAleatorio(0, 20);

    if (aleatorio < 2) {
        asteroides.push_back(
                Asteroide3D(csonido, this->pos.posicion,
                            {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                             velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                             velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                            this->pos.rotacion,
                            {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0, this->pos.escala.z / 2.0}));
    } else if (aleatorio < 14) {
        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

    } else if (aleatorio < 18) {
        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));
    } else {
        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));
>>>>>>>>> Temporary merge branch 2
    }
}
