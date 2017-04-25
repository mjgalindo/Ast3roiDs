#ifndef AST3ROIDS_ESTADOS_HPP
#define AST3ROIDS_ESTADOS_HPP

enum EstadoNave {
    REPOSO, ACELERANDO, DESTRUIDA, REAPARECIENDO
};
enum EstadoOvni {
    VIVO, EXP1, EXP2, EXP3, MUERTO
};
enum EstadoAsteroide {
    MOVIMIENTO, EXPLOSION, DESTRUIDO
};
enum Tipo {
    TIPO_0, TIPO_1, TIPO_2
};
enum Tamano {
    TAM_0, TAM_1, TAM_2
};

enum Tipo3D {
    TIPO3D_0, TIPO3D_1, TIPO3D_2
};
enum Tamano3D {
    TAM3D_0, TAM3D_1, TAM3D_2, TAM3D_FRAGMENTO
};
#endif //AST3ROIDS_ESTADOS_HPP
