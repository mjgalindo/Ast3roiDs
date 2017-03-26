#include <iostream>
#include "Nave.hpp"

//Constructor
Nave::Nave(sf::Vector2f posicion_inicial, sf::Vector2u limitesPantalla, long int *p)
        : Triangular(posicion_inicial, (float) -PI / 2.0f, 10 * (limitesPantalla.y / (float) RESOLUCION_BASE.y)) {

    if (!bufferSonidoDisparo.loadFromFile("Recursos/Sonido/fire.wav")) {
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/fire.wav\"");
    }
    if (!bufferSonidoPropulsion.loadFromFile("Recursos/Sonido/thrust.wav")) {
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/thrust.wav\"");
    }
    if (!bufferSonidoDestruccion.loadFromFile("Recursos/Sonido/bangSmall.wav")) {
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/bangSmall.wav\"");
    }

    reproductorDeSonidoPropulsion.setBuffer(bufferSonidoPropulsion);
    reproductorDeSonidoDisparos.setBuffer(bufferSonidoDisparo);
    reproductorDeSonidoDestruccion.setBuffer(bufferSonidoDestruccion);

    vs.setPrimitiveType(sf::LineStrip);
    vs.resize(3);
    vs[0].position = {1.0f, 0.0f};
    vs[1].position = {-0.7071067812f, 0.7071067812f};
    vs[2].position = {-0.7071067812f, -0.7071067812f};

    linea0.setPrimitiveType(sf::LineStrip);
    linea1.setPrimitiveType(sf::LineStrip);
    linea2.setPrimitiveType(sf::LineStrip);
    linea3.setPrimitiveType(sf::LineStrip);

    linea0.resize(2);
    linea0[0].position = {1.0f, 0.0f};
    linea0[1].position = {-0.7071067812f, 0.7071067812f};
    linea1.resize(2);
    linea1[0].position = {-0.7071067812f, 0.7071067812f};
    linea1[1].position = {-0.4f, 0.0f};
    linea2.resize(2);
    linea2[0].position = {-0.4f, 0.0f};
    linea2[1].position = {-0.7071067812f, -0.7071067812f};
    linea3.resize(2);
    linea3[0].position = {-0.7071067812f, -0.7071067812f};
    linea3[1].position = {1.0f, 0.0f};

    poligono.setPrimitiveType(sf::LineStrip);
    poligono.resize(5);
    poligono[0].position = {1.0f, 0.0f};
    poligono[1].position = {-0.7071067812f, 0.7071067812f};
    poligono[2].position = {-0.4f, 0.0f};
    poligono[3].position = {-0.7071067812f, -0.7071067812f};
    poligono[4].position = {1.0f, 0.0f};

    //fuego.setPrimitiveType(sf::LineStrip);
    fuego.setPointCount(4);
    fuego.setPoint(0, sf::Vector2f(-0.55f, 0.0f));
    fuego.setPoint(1, sf::Vector2f(-0.7f, 0.5f));
    fuego.setPoint(2, sf::Vector2f(-1.0f, 0.0f));
    fuego.setPoint(3, sf::Vector2f(-0.7f, -0.5f));
    //fuego.setPoint(0, sf::Vector2f(-0.55f, 0.0f));


    //Posicion de la nave
    pos_inicial = posicion_inicial;

    //Velocidad de la nave
    velocidad = sf::Vector2f(0.0, 0.0);

    estado = REPOSO;

    //Disparos
    num_disparos = 0;
    for (int i = 0; i < MAX_DISPAROS; i++) {
        disparos[i] = Disparo({0.0f, 0.0f}, 0.0f, limitesPantalla);
    }

    limites = limitesPantalla;
    puntuacion = p;
}

void Nave::reiniciar() {
    direccion = (float) -PI / 2.0f;
    //Posicion de la nave
    posicion = pos_inicial;
    //Velocidad de la nave
    velocidad = sf::Vector2f(0.0, 0.0);
}

//Destructor
Nave::~Nave() {}

//Setters
void Nave::setPoligono(sf::Vector2f ps[5]) {
    poligono[0].position = ps[0];
    poligono[1].position = ps[1];
    poligono[2].position = ps[2];
    poligono[3].position = ps[3];
    poligono[4].position = ps[4];
}

void Nave::setVelocidad(sf::Vector2f vel) {
    velocidad = vel;
}

void Nave::setVidas(int v) {
    vidas = v;
}

//Getters
sf::VertexArray *Nave::getPoligono() {
    return &poligono;
}

sf::Vector2f Nave::getVelocidad() {
    return velocidad;
}

int Nave::getVidas() {
    return vidas;
}

//Dibujo
void Nave::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    switch (estado) {
        case REPOSO: {
            sf::Transform t;
            t.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion).scale({tamano, tamano});

            target.draw(poligono, t);
            break;
        }

        case ACELERANDO: {
            sf::Transform t;
            t.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion).scale({tamano, tamano});

            target.draw(poligono, t);
            target.draw(fuego, t);
            break;
        }

        case DESTRUIDA: {


            sf::Transform t0, t1, t2, t3;
            t0.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion0).scale({tamano, tamano});
            t1.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion1).scale({tamano, tamano});
            t2.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion2).scale({tamano, tamano});
            t3.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion3).scale({tamano, tamano});


            target.draw(linea0, t0);
            target.draw(linea1, t1);
            target.draw(linea2, t2);
            target.draw(linea3, t3);
            break;

        }
        case REAPARECIENDO: {
            break;
        }
        default:
            break;
    }

    //Dibujar los disparos
    for (int i = 0; i < num_disparos; i++) {
        target.draw(disparos[i]);
    }
}

//Otros
void Nave::disparar() {
    if (estado == REPOSO || estado == ACELERANDO) {
        if (num_disparos < MAX_DISPAROS) {
            sf::Vector2f inicio = poligono[0].position;
            inicio.x = (float) (poligono[0].position.x * tamano * cos(direccion) -
                                poligono[0].position.y * tamano * sin(direccion));
            inicio.y = (float) (poligono[0].position.y * tamano * cos(direccion) +
                                poligono[0].position.x * tamano * sin(direccion));
            disparos[num_disparos] = Disparo(posicion + inicio, direccion, limites);
            num_disparos++;
            reproductorDeSonidoDisparos.play();
        }
    }
}

void Nave::rotarIzda() {
    if (estado == REPOSO || estado == ACELERANDO) {
        direccion -= V_ANGULAR;
        if (direccion < 0.0) {
            direccion += 2 * PI;
        }
    }
}

void Nave::rotarDcha() {
    if (estado == REPOSO || estado == ACELERANDO) {
        direccion += V_ANGULAR;
        if (direccion > 2.0 * PI) {
            direccion -= 2 * PI;
        }
    }
}

void Nave::mover(std::vector<Asteroide> &v, Circular &o) {
    if (estado == REPOSO || estado == ACELERANDO) {
        //Mover la nave
        posicion.x += velocidad.x;
        if (posicion.x - 1 >= limites.x) {
            posicion.x -= limites.x;
        } else if (posicion.x + 1 <= 0.0) {
            posicion.x += limites.x;
        }

        posicion.y += velocidad.y;
        if (posicion.y - 1 >= limites.y) {
            posicion.y -= limites.y;
        } else if (posicion.y + 1 <= 0.0) {
            posicion.y += limites.y;
        }

        //Mover los disparos
        for (int i = 0; i < num_disparos; i++) {
            disparos[i].mover();
            if (disparos[i].comprobarAlcance()) {
                if (disparos[i].comprobarAlcance()) {
                    recuperarDisparo(i);
                    i--;
                }
            }
        }

        if (o.getEstado() == VIVO && comprobarColision(o)) {
            *puntuacion += o.getPuntuacion();
            recienDestruida = true;

            o.cambiarEstado(EXP1);
            cambiarEstado(DESTRUIDA);
        }

        //Se comprueba el impacto de los disparos
        for (int j = 0; j < num_disparos; j++) {
            if (o.getEstado() == VIVO && disparos[j].comprobarColision(o)) {
                *puntuacion += o.getPuntuacion();
                recuperarDisparo(j);
                j--;

                o.cambiarEstado(EXP1);
            }
        }

        for (int i = 0; i < v.size(); i++) {
            if (v[i].estado == MOVIMIENTO) {
                if (comprobarColision(v[i])) {
                    *puntuacion += v[i].getPuntuacion();
                    cambiarEstado(DESTRUIDA);

                    //Destruir asteroide, dividirlo o lo que sea...
                    v[i].gestionarDestruccion(v);
                    v.erase(v.begin() + i);
                    i--;
                    continue;
                }
                bool detectada = false;
                //Se comprueba el impacto de los disparos
                for (int j = 0; j < num_disparos && !detectada; j++) {
                    if (disparos[j].comprobarColision(v[i])) {
                        *puntuacion += v[i].getPuntuacion();
                        recuperarDisparo(j);

                        //Destruir asteroide, dividirlo o lo que sea....
                        v[i].gestionarDestruccion(v);
                        //v.erase(v.begin() + i);
                        i--;
                        detectada = true;
                    }
                }
            }
        }
    }

    if (estado == DESTRUIDA) {
        if (recienDestruida) {
            posicion0 = posicion;
            posicion1 = posicion;
            posicion2 = posicion;
            posicion3 = posicion;
            recienDestruida = false;
        }

        posicion0 = {posicion0.x + 1.0f, posicion0.y + 1};
        posicion1 = {posicion1.x - 0.5f, posicion1.y + 1};
        posicion2 = {posicion2.x + 1.0f, posicion2.y - 1};
        posicion3 = {posicion3.x - 0.5f, posicion3.y - 1};
    }
}

void Nave::recuperarDisparo(int d) {
    for (int i = d; i < num_disparos - 1; i++) {
        disparos[i] = disparos[i + 1];
    }
    num_disparos--;
}

void Nave::acelerar() {
    if (estado == REPOSO || estado == ACELERANDO) {
        if (velocidad.x * velocidad.x + velocidad.y * velocidad.y < MAX_VELOCIDAD * MAX_VELOCIDAD) {
            velocidad.x += ACELERACION * cos(direccion) * limites.x / (float) RESOLUCION_BASE.x;
            velocidad.y += ACELERACION * sin(direccion) * limites.y / (float) RESOLUCION_BASE.y;
        }
        if (reproductorDeSonidoPropulsion.getStatus() == sf::Sound::Status::Stopped) {
            reproductorDeSonidoPropulsion.play();
        }

        cambiarEstado(REPOSO);
        cambiarEstado(ACELERANDO);
    }
}

void Nave::frenar() {
    if (velocidad.x * velocidad.x + velocidad.y * velocidad.y < UMBRAL * limites.x / (float) RESOLUCION_BASE.x) {
        velocidad.x = 0;
        velocidad.y = 0;
    } else {
        velocidad.x *= DECELERACION;
        velocidad.y *= DECELERACION;
    }
}

bool Nave::comprobarColision(Circular &c) {

    return colisionTrianguloCirculo(getTriangulo(), c.posicion, c.radio);
}

void Nave::cambiarEstado(int nuevoEstado) {
    static int ciclos = 0;

    if (nuevoEstado == DESTRUIDA && estado != nuevoEstado) {
        vidas--;
        num_disparos = 0;
        recienDestruida = true;
    }

    estado = nuevoEstado;
    switch (estado) {
        case REPOSO:
            ciclos = 0;
            break;
        case ACELERANDO:
            if (ciclos > 3) {
                ciclos = 0;
                estado = REPOSO;
            } else {
                ciclos++;
            }
            break;
        case DESTRUIDA:
            if (ciclos >= 50) {
                estado = REAPARECIENDO;
                reiniciar();
                ciclos = 0;
            } else {
                ciclos++;
            }
            break;
        case REAPARECIENDO:
            if (ciclos >= 50) {
                estado = REPOSO;
                ciclos = 0;
            } else {
                ciclos++;
            }
            break;
        default:
            break;
    }
}
