#include <SFML/Graphics.hpp>
#include <memory>
#include <thread>
#include <iostream>
#include <fstream>

#include "Graficos/Nave.hpp"
#include "Graficos/OvniInteligente.hpp"
#include "Graficos3D/Asteroide3D.hpp"
#include "Graficos3D/Nave3D.hpp"
#include "Util3D/Ventana3D.hpp"
#include "Util3D/ControladorTexturas.hpp"
#include "Util3D/ControladorShaders.hpp"
#include "Graficos3D/Esfera.hpp"

#define MAX_PUNTS 10

using namespace std;

enum Estado {
    TITULO, MENU, JUEGO2D, JUEGO3D, GAME_OVER, PUNTUACIONES, CONTROLES, OPCIONES, CREDITOS, EXIT
};
enum controles {
    GIRAR_IZQUIERDA = 0, GIRAR_DERECHA = 1, ACELERAR = 2, DISPARAR = 3, HIPERESPACIO = 4, VOLVER = 5
};

struct Configuracion {
    sf::Vector2u resolucion;
    bool pantallaCompleta;
    unsigned int volumen;
    unsigned int antialiasing;
    int colorId;
    array<sf::Color, 4u> COLORES = {sf::Color::White, sf::Color::Red, sf::Color::Green, sf::Color::Cyan};

    sf::Keyboard::Key girar_izquierda = sf::Keyboard::Left;
    sf::Keyboard::Key girar_derecha = sf::Keyboard::Right;
    sf::Keyboard::Key acelerar = sf::Keyboard::A;
    sf::Keyboard::Key disparar = sf::Keyboard::D;
    sf::Keyboard::Key hiperespacio = sf::Keyboard::Space;

    Configuracion() {
        resolucion = RESOLUCION_BASE;
        pantallaCompleta = false;
        volumen = 50;
        antialiasing = 2;
        colorId = 0;

        girar_izquierda = sf::Keyboard::Left;
        girar_derecha = sf::Keyboard::Right;
        acelerar = sf::Keyboard::A;
        disparar = sf::Keyboard::D;
        hiperespacio = sf::Keyboard::Space;
    }

    sf::Color color() {
        return COLORES[colorId];
    }

    string colorString() {
        switch (colorId) {
            case 0:
                return "BLANCO";
            case 1:
                return "ROJO";
            case 2:
                return "VERDE";
            case 3:
                return "AZUL";
            default:
                return "???";
        }
    }
};

Estado tratarTitulo(Estado estado);

Estado tratarMenu(Estado estado);

Estado tratarJuego(Estado estado);

Estado tratarJuego3D(Estado estado);

Estado tratarGameOver(Estado estado);

Estado tratarPuntuaciones(Estado estado);

Estado tratarOpciones(Estado estado);

Estado tratarControles(Estado estado);

Estado tratarCreditos(Estado estado);

Configuracion leeConfiguracion();

string keyToString(sf::Keyboard::Key k);

void escribeConfiguracion(Configuracion config);

void comprobarMuerteAsteroides(std::vector<Asteroide> &asteroides);

double ratio_alto = 1.0 / RESOLUCION_BASE.x;
double ratio_ancho = 1.0 / RESOLUCION_BASE.y;

Configuracion configuracionGlobal;
sf::Vector2u &resolucion = configuracionGlobal.resolucion;

sf::VertexArray poligono;

template<typename T>
T ajustar_h(T valor) {
    return (T) (valor * resolucion.y * ratio_alto);
}

template<typename T>
T ajustar_w(T valor) {
    return (T) (valor * resolucion.x * ratio_ancho);
}

//Ventana
sf::RenderWindow ventana;

//Puntuacion
long int puntuacion;
bool juego2D = true;

void inicializaVentana() {
    sf::ContextSettings configuracion;
    configuracion.depthBits = 24;
    configuracion.stencilBits = 8;
    configuracion.majorVersion = 3;
    configuracion.minorVersion = 3;
    configuracion.antialiasingLevel = configuracionGlobal.antialiasing;

    if (configuracionGlobal.pantallaCompleta) {
        ventana.create(sf::VideoMode(resolucion.x, resolucion.y), "Ast3roiDs", sf::Style::Fullscreen, configuracion);
        ventana.setMouseCursorVisible(false);
    } else {
        ventana.create(sf::VideoMode(resolucion.x, resolucion.y), "Ast3roiDs", sf::Style::Titlebar | sf::Style::Close,
                       configuracion);
        ventana.setMouseCursorVisible(true);
    }
    ventana.setFramerateLimit(60);
    ventana.setKeyRepeatEnabled(false);
    ventana.setVerticalSyncEnabled(true);
    ventana.requestFocus();
    sf::Image imagen;
    imagen.loadFromFile("Recursos/Icono.png");
    ventana.setIcon(imagen.getSize().x, imagen.getSize().y, imagen.getPixelsPtr());
}

sf::Font fuenteAsteroids;

inline void inicializaTexto(sf::Text &texto, unsigned int tamanoFuente, double grosorLinea = 0.3) {
    texto.setFont(fuenteAsteroids);
    texto.setOutlineThickness((float) grosorLinea);
    texto.setOutlineColor(configuracionGlobal.color());
    texto.setCharacterSize(tamanoFuente);
    texto.setFillColor(configuracionGlobal.color());
}

ControladorSonido csonido;

int main() {
    fuenteAsteroids.loadFromFile("Recursos/Fuentes/atari.ttf");
    configuracionGlobal = leeConfiguracion();
    csonido.setVolumen(configuracionGlobal.volumen);
    inicializaVentana();

    //icono nave
    poligono.setPrimitiveType(sf::LineStrip);
    poligono.resize(5);
    poligono[0].position = {1.0f, 0.0f};
    poligono[1].position = {-0.7071067812f, 0.7071067812f};
    poligono[2].position = {-0.4f, 0.0f};
    poligono[3].position = {-0.7071067812f, -0.7071067812f};
    poligono[4].position = {1.0f, 0.0f};

    for (int i = 0; i < poligono.getVertexCount(); i++) {
        poligono[i].color = configuracionGlobal.color();
    }
    Estado estado_actual = TITULO;
    while (ventana.isOpen()) {
        switch (estado_actual) {
            case TITULO:
                estado_actual = tratarTitulo(estado_actual);
                break;
            case MENU:
                estado_actual = tratarMenu(estado_actual);
                break;
            case JUEGO2D:
                estado_actual = tratarJuego(estado_actual);
                break;
            case JUEGO3D:
                estado_actual = tratarJuego3D(estado_actual);
                break;
            case GAME_OVER:
                estado_actual = tratarGameOver(estado_actual);
                break;
            case PUNTUACIONES:
                estado_actual = tratarPuntuaciones(estado_actual);
                break;
            case CONTROLES:
                estado_actual = tratarControles(estado_actual);
                ventana.setActive(true);
                break;
            case OPCIONES:
                estado_actual = tratarOpciones(estado_actual);
                ventana.setActive(true);
                break;
            case CREDITOS:
                estado_actual = tratarCreditos(estado_actual);
                break;
            default:
                return 0;
        }
    }
    return 0;
}

Estado tratarTitulo(Estado estado) {
    sf::Text titulo;
    sf::Text instrucciones;

    inicializaTexto(titulo, ajustar_h(100u), 2.5f);
    titulo.setString("AST3ROIDS");
    titulo.setPosition((resolucion.x - titulo.getLocalBounds().width) / 2, resolucion.y / 5);

    inicializaTexto(instrucciones, ajustar_h(30u));
    instrucciones.setString("<ENTER> PARA MENU");
    instrucciones.setPosition((resolucion.x - instrucciones.getLocalBounds().width) / 2, ajustar_h(400));

    sf::Clock reloj;
    bool dibujaInstrucciones = true;

    vector<Asteroide> asteroides;
    unsigned int numeroDeAsteroides = 10;
    Asteroide::nuevosAsteroidesAleatorios(asteroides, numeroDeAsteroides, resolucion, configuracionGlobal.color(),
                                          &csonido);
    Nave nave = Nave({-100, -100}, resolucion, &puntuacion, configuracionGlobal.color(), &csonido);
    Ovni ovni(resolucion, configuracionGlobal.color(), &csonido);

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return EXIT;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Return) {
                        return MENU;
                    }
                default:
                    break;
            }
        }

        ventana.clear(sf::Color::Black);
        for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
            ast->mover();
            ventana.draw(*ast);
        }
        comprobarMuerteAsteroides(asteroides);
        ovni.mover(asteroides, nave);
        ventana.draw(ovni);
        ventana.draw(titulo);
        if (reloj.getElapsedTime().asMilliseconds() > 1000) {
            dibujaInstrucciones = !dibujaInstrucciones;
            reloj.restart();
        }
        if (dibujaInstrucciones)
            ventana.draw(instrucciones);
        ventana.display();

        if (asteroides.size() == 0) {
            Asteroide::nuevosAsteroidesAleatorios(asteroides, numeroDeAsteroides, resolucion,
                                                  configuracionGlobal.color(), &csonido);
        }

        ovni.cambiarEstado(ovni.getEstado());
    }
}

Estado tratarMenu(Estado estado) {
    sf::Text texto;
    sf::Text opcion1;
    sf::Text opcion2;
    sf::Text opcion3;
    sf::Text opcion4;
    sf::Text opcion5;
    sf::Text opcion6;
    sf::Text opcion7;


    inicializaTexto(texto, ajustar_h(80u), 1.5);
    texto.setString("MENU");
    texto.setPosition({(resolucion.x - texto.getLocalBounds().width) / 2.0f, resolucion.y / 20.0f});

    inicializaTexto(opcion1, ajustar_h(40u));
    opcion1.setString("JUGAR 2D");
    opcion1.setPosition(
            {(resolucion.x - opcion1.getLocalBounds().width) / 2.0f, resolucion.y / 9 + resolucion.y / 9.0f});

    inicializaTexto(opcion2, ajustar_h(40u));
    opcion2.setString("JUGAR 3D");
    opcion2.setPosition(
            {(resolucion.x - opcion2.getLocalBounds().width) / 2.0f, resolucion.y / 9 +  2 * resolucion.y / 9.0f});

    inicializaTexto(opcion3, ajustar_h(40u));
    opcion3.setString("PUNTUACIONES");
    opcion3.setPosition(
            {(resolucion.x - opcion3.getLocalBounds().width) / 2.0f, resolucion.y / 9 + 3 * resolucion.y / 9.0f});

    inicializaTexto(opcion4, ajustar_h(40u));
    opcion4.setString("OPCIONES");
    opcion4.setPosition(
            {(resolucion.x - opcion4.getLocalBounds().width) / 2, resolucion.y / 9.0f + 4 * resolucion.y / 9.0f});

    inicializaTexto(opcion5, ajustar_h(40u));
    opcion5.setString("CONTROLES");
    opcion5.setPosition(
            {(resolucion.x - opcion5.getLocalBounds().width) / 2, resolucion.y / 9.0f + 5 * resolucion.y / 9.0f});

    inicializaTexto(opcion6, ajustar_h(40u));
    opcion6.setString("CREDITOS");
    opcion6.setPosition(
            {(resolucion.x - opcion6.getLocalBounds().width) / 2, resolucion.y / 9.0f + 6 * resolucion.y / 9.0f});

    inicializaTexto(opcion7, ajustar_h(40u));
    opcion7.setString("SALIR");
    opcion7.setPosition(
            {(resolucion.x - opcion7.getLocalBounds().width) / 2, resolucion.y / 9.0f + 7 * resolucion.y / 9.0f});

    array<Estado, 7> opciones = {JUEGO2D, JUEGO3D, PUNTUACIONES, OPCIONES, CONTROLES, CREDITOS, EXIT};
    int seleccion = 0;

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return EXIT;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Return) {
                        return opciones[seleccion];
                    } else if (event.key.code == sf::Keyboard::Up) {
                        seleccion--;
                        if (seleccion < 0) {
                            seleccion = (int) opciones.size() - 1;
                        }
                    } else if (event.key.code == sf::Keyboard::Down) {
                        seleccion++;
                        if (seleccion >= opciones.size()) {
                            seleccion = 0;
                        }
                    }
                default:
                    break;
            }
        }

        //Indicador con forma de nave
        sf::Transform t;
        switch (seleccion) {
            case 0:
                t.translate({opcion1.getPosition().x - resolucion.x / 10, opcion1.getPosition().y + ajustar_h(20u)})
                        .scale(ajustar_h(35u), ajustar_w(20u));
                break;
            case 1:
                t.translate({opcion2.getPosition().x - resolucion.x / 10, opcion2.getPosition().y + ajustar_h(20u)})
                        .scale(ajustar_h(35u), ajustar_w(20u));
                break;
            case 2:
                t.translate({opcion3.getPosition().x - resolucion.x / 10, opcion3.getPosition().y + ajustar_h(20u)})
                        .scale(ajustar_h(35u), ajustar_w(20u));
                break;
            case 3:
                t.translate({opcion4.getPosition().x - resolucion.x / 10, opcion4.getPosition().y + ajustar_h(20u)})
                        .scale(ajustar_h(35u), ajustar_w(20u));
                break;
            case 4:
                t.translate({opcion5.getPosition().x - resolucion.x / 10, opcion5.getPosition().y + ajustar_h(20u)})
                        .scale(ajustar_h(35u), ajustar_w(20u));
                break;
            case 5:
                t.translate({opcion6.getPosition().x - resolucion.x / 10, opcion6.getPosition().y + ajustar_h(20u)})
                        .scale(ajustar_h(35u), ajustar_w(20u));
                break;
            case 6:
                t.translate({opcion7.getPosition().x - resolucion.x / 10, opcion7.getPosition().y + ajustar_h(20u)})
                        .scale(ajustar_h(35u), ajustar_w(20u));
                break;
            default:
                break;
        }

        ventana.clear(sf::Color::Black);
        ventana.draw(poligono, t);
        ventana.draw(texto);
        ventana.draw(opcion1);
        ventana.draw(opcion2);
        ventana.draw(opcion3);
        ventana.draw(opcion4);
        ventana.draw(opcion5);
        ventana.draw(opcion6);
        ventana.draw(opcion7);
        ventana.display();
    }
}

/// Ejemplo de como reproducir musica. Probablemente queramos
/// desactivarlo con una tecla de mute por lo que hará falta
/// más comunicación con el thread del juego. Además, cada vez
/// debería ser más rapido dependiendo de la puntuación o del
/// avance en cada nivel.
void reproducirMusica(std::shared_ptr<bool> jugando, std::shared_ptr<bool> silencio, std::shared_ptr<bool> reiniciar,
                      int volumen) {
    sf::SoundBuffer sonido1, sonido2;
    sonido1.loadFromFile("Recursos/Sonido/beat1.wav");
    sonido2.loadFromFile("Recursos/Sonido/beat2.wav");
    sf::Sound reproductor1, reproductor2;
    reproductor1.setBuffer(sonido1);
    reproductor1.setVolume(volumen);
    reproductor2.setBuffer(sonido2);
    reproductor2.setVolume(volumen);
    int tiempoEntreSonidos = 1000;
    while (*jugando) {
        if (!*silencio) reproductor1.play();
        sf::sleep(sf::milliseconds(tiempoEntreSonidos));
        if (!*silencio) reproductor2.play();
        sf::sleep(sf::milliseconds(tiempoEntreSonidos));
        if (tiempoEntreSonidos > 200)
            tiempoEntreSonidos -= 10;
        if (*reiniciar) {
            tiempoEntreSonidos = 1000;
            *reiniciar = false;
        }
    }
}

void comprobarMuerteAsteroides(std::vector<Asteroide> &asteroides) {
    for (unsigned int i = 0; i < asteroides.size(); i++) {
        if (asteroides[i].estado == DESTRUIDO) {
            asteroides.erase(asteroides.begin() + i);
            i--;
        }
    }

}

Estado tratarJuego(Estado estado) {

    juego2D = true;

    puntuacion = 0;
    int vidas_puntuacion = 0;
    Asteroide::reiniciarNivel();

    sf::Text texto;
    sf::Text opcion1;
    sf::Text punt;

    inicializaTexto(punt, ajustar_h(30u));
    punt.setPosition({ajustar_w(20.0f), ajustar_h(10.0f)});

    shared_ptr<bool> jugando(new bool(true));
    shared_ptr<bool> silencioMusica(new bool(false));
    shared_ptr<bool> reiniciarMusica(new bool(false));

    thread musica(&reproducirMusica, jugando, silencioMusica, reiniciarMusica, configuracionGlobal.volumen * 1.5);
    sf::Clock reloj;
    int nivel = 0;

    Nave nave = Nave({resolucion.x / 2.0f, resolucion.y / 2.0f}, resolucion, &puntuacion, configuracionGlobal.color(),
                     &csonido);
    Ovni *ovni;
    Ovni ovniNormal(resolucion, configuracionGlobal.color(), &csonido);
    OvniInteligente ovniInteligente(resolucion, configuracionGlobal.color(), &csonido);
    ovni = &ovniNormal;
    bool ovniElegido = false;
    float probabilidadOvniInt = 1;
    float probabilidadOvniTon = 0.5;

    vector<Asteroide> asteroides;
    unsigned int numeroDeAsteroides = 4;
    Asteroide::nuevosAsteroidesAleatorios(asteroides, numeroDeAsteroides, resolucion, configuracionGlobal.color(),
                                          &csonido);
    //// Menu flotante pausar juego
    bool pausarJuego = false;
    sf::RectangleShape cuadroSalir1({ajustar_w(420.0f), ajustar_h(220.0f)});
    sf::RectangleShape cuadroSalir2({ajustar_w(400.0f), ajustar_h(200.0f)});
    cuadroSalir1.setFillColor(configuracionGlobal.color());
    cuadroSalir1.setPosition(configuracionGlobal.resolucion.x / 2.0f - cuadroSalir1.getSize().x / 2.0f,
                             configuracionGlobal.resolucion.y / 2.0f - cuadroSalir1.getSize().y / 2.0f);
    cuadroSalir2.setFillColor(sf::Color::Black);
    cuadroSalir2.setPosition(configuracionGlobal.resolucion.x / 2.0f - cuadroSalir2.getSize().x / 2.0f,
                             configuracionGlobal.resolucion.y / 2.0f - cuadroSalir2.getSize().y / 2.0f);
    sf::Text textoSalir;
    inicializaTexto(textoSalir, ajustar_h(30u));
    textoSalir.setString("SALIR?");
    textoSalir.setPosition(configuracionGlobal.resolucion.x / 2.0f - textoSalir.getLocalBounds().width / 2.0f,
                           configuracionGlobal.resolucion.y / 2.0f - ajustar_h(60u));

    sf::Text opcionSi;
    inicializaTexto(opcionSi, ajustar_h(30u));
    opcionSi.setString("SI");
    opcionSi.setPosition(
            configuracionGlobal.resolucion.x / 2.0f - ajustar_w(60u) - opcionSi.getLocalBounds().width / 2.0f,
            configuracionGlobal.resolucion.y / 2.0f + ajustar_h(30u));
    sf::Text opcionNo;
    inicializaTexto(opcionNo, ajustar_h(30u));
    opcionNo.setString("NO");
    opcionNo.setPosition(
            configuracionGlobal.resolucion.x / 2.0f + ajustar_w(60u) - opcionNo.getLocalBounds().width / 2.0f,
            configuracionGlobal.resolucion.y / 2.0f + ajustar_h(30u));

    enum OpcionSalir {
        SI, NO
    };
    //Easter egg
    bool NESI = false;
    clock_t tiempo;

    sf::Text tNESI;
    inicializaTexto(tNESI, ajustar_h(30u));
    tNESI.setString("NOBODY EXPECTS THE SPANISH INQUISITION");
    tNESI.setPosition(sf::Vector2f((resolucion.x - tNESI.getLocalBounds().width) / 2.0f,
                                   resolucion.y - tNESI.getLocalBounds().height - ajustar_h(20)));
    OpcionSalir seleccionSalir = NO;
    //// Bucle principal
    while (true) {
        if (*jugando and nave.getVidas() < 0) {
            *jugando = false;
            *silencioMusica = true;
            musica.join();
        }

        if (asteroides.size() == 0) {
            nivel++;
            if (probabilidadOvniInt < 0.5) {
                probabilidadOvniInt += 0.05;
            }
            if (probabilidadOvniTon > 0.1) {
                probabilidadOvniTon -= 0.05;
            }
            ovniInteligente.disminuirError();
            numeroDeAsteroides += 2;
            if (numeroDeAsteroides > 12) {
                numeroDeAsteroides = 12;
            }
            Asteroide::aumentarNivel();
            Asteroide::nuevosAsteroidesAleatorios(asteroides, numeroDeAsteroides, resolucion,
                                                  configuracionGlobal.color(), &csonido);
            *reiniciarMusica = true;
        }

        if (ovni->getEstado() == MUERTO && !ovniElegido) {
            ovniElegido = true;
            float va = valorAleatorio(0.0, 1.0);
            if (va < probabilidadOvniInt) {
                if (configuracionGlobal.color() == sf::Color::Red) {
                    NESI = true;
                    tiempo = clock();
                }
                ovni = &ovniInteligente;
            } else if (va < probabilidadOvniInt + probabilidadOvniTon) {
                ovni = &ovniNormal;
            }
        }

        sf::Event event;
        ventana.pollEvent(event);
        switch (event.type) {
            case sf::Event::Closed:
                if (*jugando) {
                    *silencioMusica = true;
                    *jugando = false;
                    musica.join();
                }
                ventana.close();
                return EXIT;
            case sf::Event::KeyPressed:
                if (*jugando) {
                    if (event.key.code == configuracionGlobal.disparar) {
                        nave.disparar();
                    } else if (event.key.code == sf::Keyboard::M) {
                        (*silencioMusica) = !*silencioMusica;
                    } else if (event.key.code == sf::Keyboard::Escape) {
                        pausarJuego = !pausarJuego;
                        *silencioMusica = pausarJuego;
                        seleccionSalir = NO;
                    } else if (pausarJuego and event.key.code == sf::Keyboard::Return) {
                        if (seleccionSalir == NO) {
                            // Continuar jugando
                            pausarJuego = false;
                            *silencioMusica = false;
                        } else {
                            // Salir del juego
                            *silencioMusica = true;
                            *jugando = false;
                            musica.join();
                            return GAME_OVER;
                        }
                    } else if (pausarJuego and event.key.code == sf::Keyboard::Left) {
                        seleccionSalir = SI;
                    } else if (pausarJuego and event.key.code == sf::Keyboard::Right) {
                        seleccionSalir = NO;
                    }
                } else {
                    return GAME_OVER;
                }
            default:
                break;
        }

        if (pausarJuego) {

            sf::Transform tPausa;
            if (seleccionSalir == SI) {
                tPausa.translate({opcionSi.getPosition().x - ajustar_w(30), opcionSi.getPosition().y + ajustar_h(20u)})
                        .scale(ajustar_h(35u), ajustar_w(20u));

            } else {
                tPausa.translate({opcionNo.getPosition().x - ajustar_w(30), opcionNo.getPosition().y + ajustar_h(20u)})
                        .scale(ajustar_h(35u), ajustar_w(20u));
            }
            ventana.draw(cuadroSalir1);
            ventana.draw(cuadroSalir2);
            ventana.draw(textoSalir);
            ventana.draw(opcionSi);
            ventana.draw(opcionNo);
            ventana.draw(poligono, tPausa);
            ventana.display();
        } else {
            if (*jugando) {
                if (sf::Keyboard::isKeyPressed(configuracionGlobal.girar_izquierda)) {
                    nave.rotarIzda();
                }
                if (sf::Keyboard::isKeyPressed(configuracionGlobal.girar_derecha)) {
                    nave.rotarDcha();
                }
                if (sf::Keyboard::isKeyPressed(configuracionGlobal.acelerar)) {
                    nave.acelerar();
                }
                if (sf::Keyboard::isKeyPressed(configuracionGlobal.hiperespacio)) {
                    nave.hiperEspacio();
                }
            }

            ovni->mover(asteroides, nave);
            nave.mover(asteroides, *ovni);
            nave.frenar();

            comprobarMuerteAsteroides(asteroides);
            punt.setString(std::to_string(puntuacion));
            punt.setString(std::to_string(puntuacion));

            ventana.clear(sf::Color::Black);
            ventana.draw(texto);
            ventana.draw(opcion1);
            ventana.draw(punt);

            if (NESI) {
                if ((clock() - tiempo) / (double) CLOCKS_PER_SEC > 4) {
                    NESI = false;
                }
                ventana.draw(tNESI);
            }
            //dibujar vidas

            for (int i = 0; i < nave.getVidas(); i++) {
                sf::Transform t;
                t.translate({ajustar_w(20.0f) * (i + 1), ajustar_h(60.0f)})
                        .scale(ajustar_h(10u), ajustar_w(6u)).rotate((float) (-PI / 2.0 * (180.0 / 3.14)));
                ventana.draw(poligono, t);
            }

            if (!(*jugando)) {
                sf::Text gameover;
                inicializaTexto(gameover, ajustar_h(30u));
                gameover.setString("GAME OVER");
                sf::Transform t;
                t.translate({ajustar_w(20.0f), ajustar_h(60.0f)});
                ventana.draw(gameover, t);
            }

            ventana.draw(nave);
            ventana.draw(*ovni);

            bool reaparicion_ok = true;
            for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
                ast->mover();
                if (distanciaEuclidea(ast->getPosicion(), nave.getPosicion()) < ajustar_h(70)) {
                    reaparicion_ok = false;
                }
                ventana.draw(*ast);
            }

            if (*jugando && reaparicion_ok && nave.getEstado() == REAPARECIENDO) {
                nave.cambiarEstado(REPOSO);
            }

            if (puntuacion - vidas_puntuacion >= 10000) {
                vidas_puntuacion += 10000;
                nave.setVidas(nave.getVidas() + 1);
                csonido.reproducir(ControladorSonido::VIDA_EXTRA);
            }

            ventana.display();
            reloj.restart();
            if (*jugando) nave.cambiarEstado(nave.getEstado());
            ovni->cambiarEstado(ovni->getEstado());
            if (ovni->getEstado() == VIVO) {
                ovniElegido = false;
            }
        }
    }
}

Estado tratarGameOver(Estado estado) {
    sf::Text texto;
    sf::Text opcion1;
    sf::Text Snombre;
    sf::Text nombre;
    sf::Text Spuntuacion;
    sf::Text punt;

    inicializaTexto(texto, ajustar_h(75u), 1.5);
    texto.setString("GAME OVER");
    texto.setPosition({(resolucion.x - texto.getLocalBounds().width) / 2.0f, resolucion.y / 14.0f});

    inicializaTexto(opcion1, ajustar_h(30u));
    opcion1.setString("ACEPTAR");
    opcion1.setPosition(sf::Vector2f(resolucion.x - opcion1.getLocalBounds().width - ajustar_w(5),
                                     resolucion.y - opcion1.getLocalBounds().height - ajustar_h(20)));


    sf::Transform t;
    t.translate({opcion1.getPosition().x - ajustar_w(30), opcion1.getPosition().y + ajustar_h(20u)})
            .scale(ajustar_h(35u), ajustar_w(20u));


    float altura = resolucion.y / 3.0f;

    inicializaTexto(Snombre, ajustar_h(30u));
    Snombre.setString("Nombre del piloto (3 letras): ");
    Snombre.setPosition(sf::Vector2f((resolucion.x - Snombre.getLocalBounds().width) / 2.0f, altura));

    char nombre_introducido[] = "AAA";
    int indice = 0;

    altura += Snombre.getLocalBounds().height + 10;

    inicializaTexto(nombre, ajustar_h(30u));
    nombre.setString(nombre_introducido);
    nombre.setPosition(sf::Vector2f((resolucion.x - nombre.getLocalBounds().width) / 2.0f, altura));

    altura += nombre.getLocalBounds().height + 30;

    inicializaTexto(Spuntuacion, ajustar_h(30u));
    Spuntuacion.setString("Puntuacion obtenida: ");
    Spuntuacion.setPosition(sf::Vector2f((resolucion.x - Spuntuacion.getLocalBounds().width) / 2.0f, altura + 10));

    altura += Spuntuacion.getLocalBounds().height + 10;
    inicializaTexto(punt, ajustar_h(30u));
    punt.setString(to_string(puntuacion));
    punt.setPosition(sf::Vector2f((resolucion.x - punt.getLocalBounds().width) / 2.0f, altura + 10));

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return EXIT;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Right) {
                        indice = indice + 1;
                        if (indice > 2) {
                            indice = 0;
                        }
                    }
                    if (event.key.code == sf::Keyboard::Left) {
                        indice = indice - 1;
                        if (indice < 0) {
                            indice = 2;
                        }
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        nombre_introducido[indice] = nombre_introducido[indice] + 1;
                        if (nombre_introducido[indice] > 'Z') {
                            nombre_introducido[indice] = 'A';
                        }
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        nombre_introducido[indice] = nombre_introducido[indice] - 1;
                        if (nombre_introducido[indice] < 'A') {
                            nombre_introducido[indice] = 'Z';
                        }
                    }
                    if (event.key.code == sf::Keyboard::Return) {
                        ifstream f_puntuaciones;
                        if (juego2D) {
                            f_puntuaciones = ifstream("puntuaciones.dat");
                        } else {
                            f_puntuaciones = ifstream("puntuaciones3D.dat");
                        }
                        vector<string> nombres(0);
                        vector<long int> punts(0);
                        string nombre_aux = "";
                        long int puntuacion_aux = 0;
                        if (f_puntuaciones.good()) {
                            for (int i = 0; !f_puntuaciones.eof(); i++) {
                                f_puntuaciones >> nombre_aux;
                                f_puntuaciones >> puntuacion_aux;

                                if (puntuacion_aux != 0) {
                                    nombres.push_back(nombre_aux);
                                    punts.push_back(puntuacion_aux);
                                    nombre_aux = "";
                                    puntuacion_aux = 0;
                                }
                            }

                            nombre_aux = nombre_introducido;
                            puntuacion_aux = puntuacion;
                            if (punts.empty()) {
                                nombres.push_back(nombre_aux);
                                punts.push_back(puntuacion_aux);
                            } else {
                                for (int i = 0; i < nombres.size(); i++) {
                                    if (puntuacion_aux > punts[i]) {
                                        long int p = punts[i];
                                        string n = nombres[i];
                                        punts[i] = puntuacion_aux;
                                        nombres[i] = nombre_aux;
                                        puntuacion_aux = p;
                                        nombre_aux = n;
                                    }
                                }

                                if (nombres.size() < MAX_PUNTS) {
                                    nombres.push_back(nombre_aux);
                                    punts.push_back(puntuacion_aux);
                                }
                            }
                        }
                        f_puntuaciones.close();

                        ofstream f_puntuaciones_out;
                        if (juego2D) {
                            f_puntuaciones_out = ofstream("puntuaciones.dat");
                        }
                        else{
                            f_puntuaciones_out = ofstream("puntuaciones3D.dat");
                        }
                        if (f_puntuaciones_out.good()) {
                            if (nombres.size() != 0) {
                                for (int i = 0; i < nombres.size(); i++) {
                                    f_puntuaciones_out << nombres[i] << " " << punts[i] << endl;
                                }
                            } else {
                                f_puntuaciones_out << nombre_introducido << " " << puntuacion << endl;
                            }

                            f_puntuaciones_out.flush();
                            f_puntuaciones_out.close();
                        }
                        return PUNTUACIONES;
                    }
                default:
                    break;
            }

            sf::VertexArray seleccionada(sf::LinesStrip, 2);
            seleccionada[0].position = {nombre.getPosition().x + indice * nombre.getLocalBounds().width / 3.0f,
                                        nombre.getPosition().y + nombre.getLocalBounds().height + 4};
            seleccionada[1].position = {nombre.getPosition().x + (indice + 1) * nombre.getLocalBounds().width / 3.0f,
                                        nombre.getPosition().y + nombre.getLocalBounds().height + 4};
            seleccionada[0].color = configuracionGlobal.color();
            seleccionada[1].color = configuracionGlobal.color();
            ventana.clear(sf::Color::Black);
            ventana.draw(texto);
            ventana.draw(opcion1);
            ventana.draw(poligono, t);
            ventana.draw(Snombre);
            nombre.setString(nombre_introducido);
            ventana.draw(nombre);
            ventana.draw(seleccionada);
            ventana.draw(Spuntuacion);
            ventana.draw(punt);
            ventana.display();
        }
    }
}

Estado tratarPuntuaciones(Estado estado) {
    sf::Text texto;
    sf::Text opcion1;
    sf::Text opcion2;

    vector<sf::Text> punts(MAX_PUNTS);
    vector<sf::Text> punts3D(MAX_PUNTS);

    ifstream f_puntuaciones("puntuaciones.dat");
    ifstream f_puntuaciones3D("puntuaciones3D.dat");
    if (f_puntuaciones.good()) {
        string nombre_aux;
        long int puntuacion_aux;
        for (int i = 0; i < MAX_PUNTS && !f_puntuaciones.eof(); i++) {
            f_puntuaciones >> nombre_aux;
            f_puntuaciones >> puntuacion_aux;

            string linea = "";
            linea.append(nombre_aux);
            linea.append("    ");
            linea.append(to_string(puntuacion_aux));

            if (nombre_aux.compare("") != 0) {
                nombre_aux = "";
                puntuacion_aux = 0;

                sf::Text punt;
                inicializaTexto(punt, ajustar_h(30u));
                punt.setString(linea);
                punt.setPosition({(resolucion.x - punt.getLocalBounds().width) / 2.0f,
                                  resolucion.y / 3.5f + i * resolucion.y / 14.0f});

                punts.push_back(punt);
            }
        }
    }
    f_puntuaciones.close();

    if (f_puntuaciones3D.good()) {
        string nombre_aux;
        long int puntuacion_aux;
        for (int i = 0; i < MAX_PUNTS && !f_puntuaciones3D.eof(); i++) {
            f_puntuaciones3D >> nombre_aux;
            f_puntuaciones3D >> puntuacion_aux;

            string linea = "";
            linea.append(nombre_aux);
            linea.append("    ");
            linea.append(to_string(puntuacion_aux));

            if (nombre_aux.compare("") != 0) {
                nombre_aux = "";
                puntuacion_aux = 0;

                sf::Text punt;
                inicializaTexto(punt, ajustar_h(30u));
                punt.setString(linea);
                punt.setPosition({(resolucion.x - punt.getLocalBounds().width) / 2.0f,
                                  resolucion.y / 3.5f + i * resolucion.y / 14.0f});

                punts3D.push_back(punt);
            }
        }
    }
    f_puntuaciones3D.close();

    inicializaTexto(texto, ajustar_h(60u), 1.5);
    texto.setString("PUNTUACIONES ( 2D )");
    texto.setPosition({(resolucion.x - texto.getLocalBounds().width) / 2.0f, resolucion.y / 14.0f});

    inicializaTexto(opcion1, ajustar_h(30u));
    opcion1.setString("ACEPTAR");
    opcion1.setCharacterSize(ajustar_h(30u));
    opcion1.setPosition(sf::Vector2f(resolucion.x - opcion1.getLocalBounds().width - ajustar_w(5),
                                     resolucion.y - opcion1.getLocalBounds().height - ajustar_h(20)));

    inicializaTexto(opcion2, ajustar_h(30u));
    opcion2.setString("[TAB PARA CAMBIAR MODO]");
    opcion2.setCharacterSize(ajustar_h(30u));
    opcion2.setPosition(sf::Vector2f(0,resolucion.y - opcion1.getLocalBounds().height - ajustar_h(20)));

    sf::Transform t;
    t.translate({opcion1.getPosition().x - ajustar_w(30), opcion1.getPosition().y + ajustar_h(20u)})
            .scale(ajustar_h(35u), ajustar_w(20u));

    bool mostrar2D = true;
    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return EXIT;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Return) {
                        return MENU;
                    }
                    else if (event.key.code == sf::Keyboard::Tab) {
                        mostrar2D = !mostrar2D;
                        if(mostrar2D) {
                            texto.setString("PUNTUACIONES ( 2D )");
                        }
                        else{
                            texto.setString("PUNTUACIONES ( 3D )");
                        }
                    }
                default:
                    break;
            }

            ventana.clear(sf::Color::Black);
            ventana.draw(texto);
            ventana.draw(opcion1);
            ventana.draw(opcion2);
            ventana.draw(poligono, t);


            if(mostrar2D) {
                for (unsigned int i = 0; i < punts.size(); i++) {
                    ventana.draw(punts[i]);
                }
            }
            else{
                for (unsigned int i = 0; i < punts3D.size(); i++) {
                    ventana.draw(punts3D[i]);
                }
            }

            ventana.display();
        }
    }
}

Estado tratarOpciones(Estado estado) {
    sf::Text titulo;
    sf::Text opcion1;

    configuracionGlobal = leeConfiguracion();

    inicializaTexto(titulo, ajustar_h(75u), 1.5);
    titulo.setString("OPCIONES");
    titulo.setPosition({(resolucion.x - titulo.getLocalBounds().width) / 2.0f, resolucion.y / 14.0f});

    vector<sf::Vector2u> resoluciones = resolucionesValidas();
    int resId = 0;
    for (int i = 0; i < resoluciones.size(); i++) {
        if (resoluciones[i].y == configuracionGlobal.resolucion.y and
            resoluciones[i].x == configuracionGlobal.resolucion.x) {
            resId = i;
            break;
        }
    }

    enum Opcion {
        RESOLUCION = 0, PANTALLA_COMPLETA = 1, VOLUMEN = 2, ANTIALIASING = 3, COLOR = 4, VOLVER = 5
    };

    static constexpr int OPCIONES = 6;

    array<tuple<string, string>, OPCIONES> textos{
            make_tuple("RESOLUCION", ""),
            make_tuple("PANTALLA COMPLETA", ""),
            make_tuple("VOLUMEN", ""),
            make_tuple("ANTIALIASING", ""),
            make_tuple("COLOR", ""),
            make_tuple("VOLVER", "")
    };
    array<tuple<sf::Text, sf::Text>, OPCIONES> opciones;

    float opcionX = resolucion.x / OPCIONES + 1;
    float opcionY = (resolucion.y - titulo.getPosition().y - titulo.getLocalBounds().height - ajustar_h(30u)) /
                    (float) (OPCIONES + 1);
    float offsetVertical = titulo.getPosition().y + titulo.getLocalBounds().height + ajustar_h(30u);

    for (unsigned int i = 0; i < OPCIONES; i++) {
        inicializaTexto(get<0>(opciones[i]), ajustar_h(30u));
        inicializaTexto(get<1>(opciones[i]), ajustar_h(30u));

        get<0>(opciones[i]).setString(get<0>(textos[i]));
        get<1>(opciones[i]).setString(get<1>(textos[i]));

        get<0>(opciones[i]).setPosition({opcionX, offsetVertical + opcionY * (i + 1)});
        get<1>(opciones[i]).setPosition({resolucion.x - 2 * opcionX, offsetVertical + opcionY * (i + 1)});
    }

    Opcion seleccion = RESOLUCION;
    bool fin = false;
    while (!fin) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return EXIT;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Up) {
                        seleccion = (Opcion) (seleccion - 1);
                        if (seleccion < 0) {
                            seleccion = (Opcion) (opciones.size() - 1);
                        }
                    } else if (event.key.code == sf::Keyboard::Down) {
                        seleccion = (
                                Opcion) (seleccion + 1);
                        if (seleccion >= opciones.size()) {
                            seleccion = (Opcion) 0;
                        }
                    } else if (event.key.code == sf::Keyboard::Return) {
                        if (seleccion == VOLVER) fin = true;
                    } else if (event.key.code == sf::Keyboard::Left) {
                        switch (seleccion) {
                            case RESOLUCION:
                                resId = (resId - 1) < 0 ? (int) resoluciones.size() - 1 : resId - 1;
                                break;
                            case PANTALLA_COMPLETA:
                                configuracionGlobal.pantallaCompleta = false;
                                break;
                            case VOLUMEN:
                                if (configuracionGlobal.volumen != 0) {
                                    configuracionGlobal.volumen = configuracionGlobal.volumen - 10;
                                }
                                break;
                            case ANTIALIASING:
                                configuracionGlobal.antialiasing /= 2;
                                break;
                            case COLOR:
                                configuracionGlobal.colorId = (int) ((configuracionGlobal.colorId - 1) %
                                                                     configuracionGlobal.COLORES.size());
                            default:
                                break;
                        }
                    } else if (event.key.code == sf::Keyboard::Right) {
                        switch (seleccion) {
                            case RESOLUCION:
                                resId = (resId + 1) > resoluciones.size() - 1 ? 0 : resId + 1;
                                break;
                            case PANTALLA_COMPLETA:
                                configuracionGlobal.pantallaCompleta = true;
                                break;
                            case VOLUMEN:
                                configuracionGlobal.volumen =
                                        configuracionGlobal.volumen + 10 <= 100 ? configuracionGlobal.volumen + 10
                                                                                : 100;
                                break;
                            case ANTIALIASING:
                                if (configuracionGlobal.antialiasing == 0) configuracionGlobal.antialiasing = 2;
                                else configuracionGlobal.antialiasing *= 2;
                                configuracionGlobal.antialiasing =
                                        configuracionGlobal.antialiasing > 8 ? 8u : configuracionGlobal.antialiasing;
                                break;
                            case COLOR:
                                configuracionGlobal.colorId = (int) ((configuracionGlobal.colorId + 1) %
                                                                     configuracionGlobal.COLORES.size());
                            default:
                                break;
                        }
                    }
                default:
                    break;
            }

        }

        get<1>(textos[RESOLUCION]) = to_string(resoluciones[resId].x) + "x" + to_string(resoluciones[resId].y);
        get<1>(textos[PANTALLA_COMPLETA]) = configuracionGlobal.pantallaCompleta ? "SI" : "NO";
        get<1>(textos[ANTIALIASING]) = to_string(configuracionGlobal.antialiasing);
        get<1>(textos[VOLUMEN]) = to_string(configuracionGlobal.volumen);
        get<1>(textos[COLOR]) = configuracionGlobal.colorString();
        for (unsigned int i = 0; i < OPCIONES; i++) {
            get<0>(opciones[i]).setString(get<0>(textos[i]));
            get<1>(opciones[i]).setString(get<1>(textos[i]));
        }
        sf::Transform t;
        t.translate({opcionX - ajustar_w(30), offsetVertical + opcionY * (seleccion + 1) + ajustar_h(20u)})
                .scale(ajustar_h(35u), ajustar_w(20u));

        ventana.clear(sf::Color::Black);
        ventana.draw(titulo);
        for (auto opcion : opciones) {
            ventana.draw(get<0>(opcion));
            ventana.draw(get<1>(opcion));
        }
        ventana.draw(poligono, t);
        ventana.display();
    }
    configuracionGlobal.resolucion = resoluciones[resId];
    escribeConfiguracion(configuracionGlobal);
    csonido.setVolumen(configuracionGlobal.volumen);
    for (int i = 0; i < poligono.getVertexCount(); i++) {
        poligono[i].color = configuracionGlobal.color();
    }
    inicializaVentana();
    return MENU;
}

bool controlValido(controles c, sf::Keyboard::Key k) {
    if (GIRAR_IZQUIERDA != c && configuracionGlobal.girar_izquierda == k) {
        return false;
    }
    if (GIRAR_DERECHA != c && configuracionGlobal.girar_derecha == k) {
        return false;
    }
    if (ACELERAR != c && configuracionGlobal.acelerar == k) {
        return false;
    }
    if (DISPARAR != c && configuracionGlobal.disparar == k) {
        return false;
    }
    if (HIPERESPACIO != c && configuracionGlobal.hiperespacio == k) {
        return false;
    }
    return true;
}

Estado tratarControles(Estado estado) {
    sf::Text texto;
    sf::Text opcion1;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/atari.ttf");

    configuracionGlobal = leeConfiguracion();
    csonido = ControladorSonido(configuracionGlobal.volumen);

    inicializaTexto(texto, ajustar_h(75u), 1.5);
    texto.setString("CONTROLES");
    texto.setPosition({(resolucion.x - texto.getLocalBounds().width) / 2.0f, resolucion.y / 14.0f});

    static constexpr int OPCIONES = 6;

    array<tuple<string, string>, OPCIONES> textos{
            make_tuple("GIRAR IZQUIERDA", ""),
            make_tuple("GIRAR DERECHA", ""),
            make_tuple("ACELERAR", ""),
            make_tuple("DISPARAR", ""),
            make_tuple("HIPERESPACIO", ""),
            make_tuple("VOLVER", "")
    };
    array<tuple<sf::Text, sf::Text>, OPCIONES> opciones;

    float opcionX = resolucion.x / OPCIONES + 1;
    float opcionY = (resolucion.y - texto.getPosition().y - texto.getLocalBounds().height - ajustar_h(30u)) /
                    (float) (OPCIONES + 1);
    float offsetVertical = texto.getPosition().y + texto.getLocalBounds().height + ajustar_h(30u);

    for (unsigned int i = 0; i < OPCIONES; i++) {
        inicializaTexto(get<0>(opciones[i]), ajustar_h(30u));
        inicializaTexto(get<1>(opciones[i]), ajustar_h(30u));

        get<0>(opciones[i]).setString(get<0>(textos[i]));
        get<1>(opciones[i]).setString(get<1>(textos[i]));

        get<0>(opciones[i]).setPosition({opcionX, offsetVertical + opcionY * (i + 1)});
        get<1>(opciones[i]).setPosition({resolucion.x - 2 * opcionX, offsetVertical + opcionY * (i + 1)});
    }

    controles seleccion = GIRAR_IZQUIERDA;
    bool fin = false;
    bool editando = false;
    while (!fin) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return EXIT;
                case sf::Event::KeyPressed:
                    if (editando) {
                        if (event.key.code == sf::Keyboard::Return) {
                            editando = false;
                        } else {
                            switch (seleccion) {
                                case GIRAR_IZQUIERDA:
                                    if (controlValido(GIRAR_IZQUIERDA, event.key.code)) {

                                        configuracionGlobal.girar_izquierda = event.key.code;
                                    }
                                    break;
                                case GIRAR_DERECHA:
                                    if (controlValido(GIRAR_DERECHA, event.key.code)) {
                                        configuracionGlobal.girar_derecha = event.key.code;
                                    }
                                    break;
                                case ACELERAR:
                                    if (controlValido(ACELERAR, event.key.code)) {
                                        configuracionGlobal.acelerar = event.key.code;
                                    }
                                    break;
                                case DISPARAR:
                                    if (controlValido(DISPARAR, event.key.code)) {
                                        configuracionGlobal.disparar = event.key.code;
                                    }
                                    break;
                                case HIPERESPACIO:
                                    if (controlValido(HIPERESPACIO, event.key.code)) {
                                        configuracionGlobal.hiperespacio = event.key.code;
                                    }
                                    break;
                                default:
                                    break;
                            }
                        }

                    } else if (event.key.code == sf::Keyboard::Up) {
                        seleccion = (controles) (seleccion - 1);
                        if (seleccion < 0) {
                            seleccion = (controles) (opciones.size() - 1);
                        }
                    } else if (event.key.code == sf::Keyboard::Down) {
                        seleccion = (controles) (seleccion + 1);
                        if (seleccion >= opciones.size()) {
                            seleccion = (controles) 0;
                        }
                    } else if (event.key.code == sf::Keyboard::Return) {
                        if (seleccion == VOLVER) fin = true;
                        else {
                            editando = true;
                        }
                    }
                    break;
                default:
                    break;
            }

        }

        if (configuracionGlobal.girar_izquierda >= 0 && configuracionGlobal.girar_izquierda < 26) {
            get<1>(textos[GIRAR_IZQUIERDA]) = configuracionGlobal.girar_izquierda - sf::Keyboard::A + 'A';
        } else {
            get<1>(textos[GIRAR_IZQUIERDA]) = keyToString(configuracionGlobal.girar_izquierda);
        }
        if (configuracionGlobal.girar_derecha >= 0 && configuracionGlobal.girar_derecha < 26) {
            get<1>(textos[GIRAR_DERECHA]) = configuracionGlobal.girar_derecha - sf::Keyboard::A + 'A';
        } else {
            get<1>(textos[GIRAR_DERECHA]) = keyToString(configuracionGlobal.girar_derecha);
        }
        if (configuracionGlobal.acelerar >= 0 && configuracionGlobal.acelerar < 26) {
            get<1>(textos[ACELERAR]) = configuracionGlobal.acelerar - sf::Keyboard::A + 'A';
        } else {
            get<1>(textos[ACELERAR]) = keyToString(configuracionGlobal.acelerar);
        }
        if (configuracionGlobal.disparar >= 0 && configuracionGlobal.disparar < 26) {
            get<1>(textos[DISPARAR]) = configuracionGlobal.disparar - sf::Keyboard::A + 'A';
        } else {
            get<1>(textos[DISPARAR]) = keyToString(configuracionGlobal.disparar);
        }
        if (configuracionGlobal.hiperespacio >= 0 && configuracionGlobal.hiperespacio < 26) {
            get<1>(textos[HIPERESPACIO]) = configuracionGlobal.hiperespacio - sf::Keyboard::A + 'A';
        } else {
            get<1>(textos[HIPERESPACIO]) = keyToString(configuracionGlobal.hiperespacio);
        }

        for (unsigned int i = 0; i < OPCIONES; i++) {
            get<0>(opciones[i]).setString(get<0>(textos[i]));
            get<1>(opciones[i]).setString(get<1>(textos[i]));
        }

        ventana.clear(sf::Color::Black);

        sf::Transform t;
        t.translate({opcionX - ajustar_w(30), offsetVertical + opcionY * (seleccion + 1) + ajustar_h(20u)})
                .scale(ajustar_h(35u), ajustar_w(20u));
        if (editando) {
            sf::VertexArray seleccionada(sf::LinesStrip, 2);
            seleccionada[0].position = sf::Vector2f(
                    get<1>(opciones[seleccion]).getPosition().x +
                    get<1>(opciones[seleccion]).getLocalBounds().width / 3.0 - 10,
                    get<1>(opciones[seleccion]).getPosition().y + get<1>(opciones[seleccion]).getLocalBounds().height +
                    4);
            seleccionada[1].position = sf::Vector2f(
                    get<1>(opciones[seleccion]).getPosition().x +
                    get<1>(opciones[seleccion]).getLocalBounds().width / 3.0 + 25,
                    get<1>(opciones[seleccion]).getPosition().y + get<1>(opciones[seleccion]).getLocalBounds().height +
                    4);
            seleccionada[0].color = configuracionGlobal.color();
            seleccionada[1].color = configuracionGlobal.color();
            ventana.draw(seleccionada);
        }
        ventana.draw(texto);
        for (auto opcion : opciones) {
            ventana.draw(get<0>(opcion));
            ventana.draw(get<1>(opcion));
        }
        ventana.draw(poligono, t);
        ventana.display();
    }
    escribeConfiguracion(configuracionGlobal);
    return MENU;
}

Configuracion leeConfiguracion() {
    ifstream fichConfig("opciones.cfg");
    Configuracion retVal;
    if (!fichConfig.good()) return retVal;
    unsigned int resVertical = 0;
    int gir_izq, gir_der, acel, disp, hiper;
    fichConfig >> resVertical >> retVal.pantallaCompleta >> retVal.volumen >> retVal.antialiasing >> retVal.colorId
               >> gir_izq >> gir_der >> acel >> disp >> hiper;
    if (gir_izq != 0) {
        retVal.girar_izquierda = (sf::Keyboard::Key) gir_izq;
    }
    if (gir_der != 0) {
        retVal.girar_derecha = (sf::Keyboard::Key) gir_der;
    }
    if (disp != 0) {
        retVal.disparar = (sf::Keyboard::Key) disp;
    }
    if (acel != 0) {
        retVal.acelerar = (sf::Keyboard::Key) acel;
    }
    if (hiper != 0) {
        retVal.hiperespacio = (sf::Keyboard::Key) hiper;
    }
    retVal.resolucion = {(unsigned int) (RESOLUCION_BASE.x / (RESOLUCION_BASE.y / (float) resVertical)), resVertical};
    return retVal;
}

void escribeConfiguracion(Configuracion config) {
    ofstream fichConfig("opciones.cfg");
    fichConfig << config.resolucion.y << ' ' << config.pantallaCompleta << ' ' << config.volumen << ' '
               << config.antialiasing << ' ' << config.colorId << ' ' << config.girar_izquierda << ' '
               << config.girar_derecha << ' ' << config.acelerar << ' ' << config.disparar << ' '
               << config.hiperespacio;
}

string keyToString(sf::Keyboard::Key k) {
    if (k == sf::Keyboard::RShift || k == sf::Keyboard::LShift) {
        return "Shift";
    } else if (k == sf::Keyboard::RControl || k == sf::Keyboard::LControl) {
        return "Ctrl";
    } else if (k == sf::Keyboard::RAlt || k == sf::Keyboard::LAlt) {
        return "Alt";
    } else if (k == sf::Keyboard::Space || k == sf::Keyboard::LControl) {
        return "Space";
    } else if (k == sf::Keyboard::Left) {
        return "Left";
    } else if (k == sf::Keyboard::Right) {
        return "Right";
    } else if (k == sf::Keyboard::Up) {
        return "Up";
    } else if (k == sf::Keyboard::Down) {
        return "Down";
    }
    return to_string(k);
}

Estado tratarCreditos(Estado estado) {
    sf::Text texto;
    sf::Text opcion1;
    sf::Text opcion2;
    sf::Text opcion3;
    sf::Text opcion4;

    inicializaTexto(texto, ajustar_h(75u), 1.5);
    inicializaTexto(opcion1, ajustar_h(30u), 1.5);
    inicializaTexto(opcion2, ajustar_h(30u), 1.5);
    inicializaTexto(opcion3, ajustar_h(30u), 1.5);
    inicializaTexto(opcion4, ajustar_h(30u), 1.5);

    string creditos1 = "JORGE ANDRES GALINDO (679155)";
    string creditos2 = "MIGUEL JORGE GALINDO (679954)";
    string creditos3 = "ALEJANDRO FERNANDEZ POZA (679890)";
    string creditos4 = "ADRIAN ALEJANDRE ESCRICHE (682237)";
    texto.setString("CREDITOS");

    opcion1.setString(creditos1);
    opcion2.setString(creditos2);
    opcion3.setString(creditos3);
    opcion4.setString(creditos4);

    texto.setPosition({(resolucion.x - texto.getLocalBounds().width) / 2.0f, resolucion.y / 14.0f});;
    opcion1.setPosition({(resolucion.x - opcion1.getLocalBounds().width) / 2, (float) resolucion.y});
    opcion2.setPosition({(resolucion.x - opcion2.getLocalBounds().width) / 2,
                         opcion1.getPosition().y + opcion1.getLocalBounds().height + ajustar_h(25u)});
    opcion3.setPosition({(resolucion.x - opcion3.getLocalBounds().width) / 2,
                         opcion2.getPosition().y + opcion2.getLocalBounds().height + ajustar_h(25u)});
    opcion4.setPosition({(resolucion.x - opcion4.getLocalBounds().width) / 2,
                         opcion3.getPosition().y + opcion3.getLocalBounds().height + ajustar_h(25u)});

    sf::Clock reloj;
    reloj.restart();
    bool salir = false;
    while (true) {
        sf::Event event;
        if(ventana.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return EXIT;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        return MENU;
                    }
                    break;
            }
        }

        if (reloj.getElapsedTime().asMilliseconds() > 150) {
            if (opcion1.getCharacterSize() >= ajustar_h(20) &&
                opcion1.getPosition().y + opcion1.getLocalBounds().height + resolucion.y / 6.0 < resolucion.y) {
                opcion1.setCharacterSize(opcion1.getCharacterSize() - 1);
            }

            if (opcion2.getCharacterSize() >= ajustar_h(20) &&
                opcion2.getPosition().y + opcion2.getLocalBounds().height + resolucion.y / 6.0 < resolucion.y) {
                opcion2.setCharacterSize(opcion2.getCharacterSize() - 1);
            }

            if (opcion3.getCharacterSize() >= ajustar_h(20) &&
                opcion3.getPosition().y + opcion3.getLocalBounds().height + resolucion.y / 6.0 < resolucion.y) {
                opcion3.setCharacterSize(opcion3.getCharacterSize() - 1);
            }

            if (opcion4.getCharacterSize() >= ajustar_h(20) &&
                opcion4.getPosition().y + opcion4.getLocalBounds().height + resolucion.y / 6.0 < resolucion.y) {
                opcion4.setCharacterSize(opcion4.getCharacterSize() - 1);
            }
            reloj.restart();
        }

        if(opcion4.getPosition().y + opcion4.getLocalBounds().height < 0){
            return MENU;
        }

        opcion1.setPosition((resolucion.x - opcion1.getLocalBounds().width) / 2, opcion1.getPosition().y - 1);
        opcion2.setPosition((resolucion.x - opcion2.getLocalBounds().width) / 2, opcion2.getPosition().y - 1);
        opcion3.setPosition((resolucion.x - opcion3.getLocalBounds().width) / 2, opcion3.getPosition().y - 1);
        opcion4.setPosition((resolucion.x - opcion4.getLocalBounds().width) / 2, opcion4.getPosition().y - 1);

        ventana.clear(sf::Color::Black);

        ventana.draw(texto);
        ventana.draw(opcion1);
        ventana.draw(opcion2);
        ventana.draw(opcion3);
        ventana.draw(opcion4);
        ventana.display();
    }

    return MENU;
}

/**
 * De: https://guidedhacking.com/showthread.php?6588-OpenGL-Draw-a-crosshair
 * Dibuja una cruz en el centro de la ventana.
 */
void dibujaCruz(sf::Vector2u tamVentana) {
    glPushMatrix();
    glViewport(0, 0, tamVentana.x, tamVentana.y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, tamVentana.x, tamVentana.y, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3ub(240, 240, 240);//white
    glLineWidth(2.0);
    glBegin(GL_LINES);
    //horizontal line
    glVertex2i(tamVentana.x / 2 - 7, tamVentana.y / 2);
    glVertex2i(tamVentana.x / 2 + 7, tamVentana.y / 2);
    glEnd();
    //vertical line
    glBegin(GL_LINES);
    glVertex2i(tamVentana.x / 2, tamVentana.y / 2 + 7);
    glVertex2i(tamVentana.x / 2, tamVentana.y / 2 - 7);
    glEnd();

    glPopMatrix();
}

Estado tratarJuego3D(Estado estado) {
    puntuacion = 0;
    juego2D = false;

    // Reinicializa la ventana para evitar modelos transparentes
    inicializaVentana();
    ventana.setMouseCursorVisible(false);
    ventana.setMouseCursorGrabbed(true);
    GLenum status = glewInit();
    if (status != GLEW_OK) {
        cerr << "Glew no ha podido inicializarse" << endl;
    }

    // Activa test de profundidad para ocluir triangulos que se encuentran detrás de otros.
    glEnable(GL_DEPTH_TEST);

    // Inicializa los modelos 3D y las texturas. Estos objetos solo existe para controlar
    // la creacion y destrucción de recursos. Se iniciarán siempre que se empiece a jugar.
    ControladorModelos __controladorModelos;
    ControladorTexturas __controladorTexturas;
    ControladorShaders __controladorShaders;

    unique_ptr<ControladorSonido> csonido{new ControladorSonido};

    // Inicializa shaders y texturas.
    ControladorShaders::getShader(ControladorShaders::SIMPLE)->bind();
    ControladorShaders::getShader(ControladorShaders::SIMPLE)->setDireccionLuz({0.0f, -0.75f, 0.25f});
    ControladorShaders::getShader(ControladorShaders::BRILLO)->bind();
    ControladorShaders::getShader(ControladorShaders::BRILLO)->setDireccionLuz({0.0f, -0.75f, 0.25f});

    Esfera espacio(ControladorTexturas::ESPACIO, {0, 0, 0}, {800, 800, 800});

    const float RADIO_ESFERA_JUGABLE = 100.0f;
    const float DISTANCIA_RENDER_PELIGRO = 50.0f;
    Esfera mallaLimites(ControladorTexturas::BLANCO, {0, 0, 0},
                        {RADIO_ESFERA_JUGABLE, RADIO_ESFERA_JUGABLE, RADIO_ESFERA_JUGABLE}, true);

    // Carga asteroides para ver como se mueve la nave
    vector<Asteroide3D> asteroides;
    int numeroDeAsteroides = 4;
    for (int i = 0; i < numeroDeAsteroides; i++)
        asteroides.emplace_back(csonido.get(), RADIO_ESFERA_JUGABLE);

    Nave3D nave(csonido.get(), &puntuacion, RADIO_ESFERA_JUGABLE);
    nave.teclaAcelerar = configuracionGlobal.acelerar;
    Ovni3D ovni(csonido.get(), RADIO_ESFERA_JUGABLE);

    Camara camara({0.0f, 0.0f, 0.0f}, Ventana3D::FOV, (float) ventana.getSize().x / (float) ventana.getSize().y,
                  Ventana3D::Z_NEAR, Ventana3D::Z_FAR);
    bool camaraPrimeraPersona = false;
    bool running = true;

    int nivel = 1;
    while (running) {
        if (asteroides.size() == 0) {
            nivel++;
            if (numeroDeAsteroides > 12) {
                numeroDeAsteroides = 12;
            }
            else{
                numeroDeAsteroides+=2;
            }

            for(int i=0 ; i<numeroDeAsteroides ; i++){
                asteroides.emplace_back(csonido.get(), RADIO_ESFERA_JUGABLE);
            }
        }
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        nave.disparar();
                        break;
                    }
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::F) {
                        camaraPrimeraPersona = !camaraPrimeraPersona;
                        break;
                    } else if (event.key.code == configuracionGlobal.disparar) {
                        nave.disparar();
                        break;
                    } else if (event.key.code != sf::Keyboard::Escape) { break; }
                case sf::Event::Closed:
                    running = false;
                    break;
                default:
                    break;
            }
        }
        // Si no se está mirando a la pantalla se pausa el juego
        if (!ventana.hasFocus()) {
            sf::sleep(sf::milliseconds(30));
            continue;
        }

        // Actualiza todos los elementos visibles

        sf::Vector2i posCursor = sf::Mouse::getPosition(ventana);

        nave.actualizar(nivel, asteroides, ovni, {posCursor.x - (int) resolucion.x / 2, posCursor.y - (int) resolucion.y / 2});
        if (ventana.hasFocus()) sf::Mouse::setPosition({(int) resolucion.x / 2, (int) resolucion.y / 2}, ventana);

        if (nave.getVidas() < 0) {
            running=false;
        }

        ovni.actualizar(nivel, asteroides, nave);

        // Mueve todos los asteroides y elimina los que estén destruidos.
        for (int i = 0; i < asteroides.size(); ++i) {
            asteroides[i].actualizar();
            if (asteroides[i].estado == Elemento3D::DESTRUIDO) {
                asteroides.erase(asteroides.begin() + i);
                i--;
            }
        }

        // Actualiza la cámara con respecto a la posicion de la nave utilizando su matriz modelo-mundo.
        glm::mat4 modeloNave = nave.pos.matrizModelo();
        if (camaraPrimeraPersona) {
            camara.pos = glm::vec3(modeloNave * glm::vec4(2.0f, 2.0f, 0.0f, 1.0f));
        } else {
            camara.pos = glm::vec3(modeloNave * glm::vec4(-30.0f, 4.0f, 0.0f, 1.0f));
        }
        camara.forward = glm::vec3(modeloNave * nave.DIRECCION_FRENTE_INICIAL);

        // Mantiene el vector up de la cámara apuntando hacia arriba
        camara.up = glm::cross(camara.forward, // Implementación tentativa, hasta que no gire bien la nave...
                               glm::vec3(modeloNave * glm::vec4{0.0f, 0.0f, -1.0f, 0.0f}));

        // Limpia la ventana
        glClearColor(0.0f, 0.0f, 0.0f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Dibuja todos los elementos
        for (const Asteroide3D &asteroide : asteroides) {
            asteroide.dibujar(ventana, camara);
        }

        // Si la nave está cerca del límite jugable considera si hay que renderizar los asteroides cercanos a su antípoda
        if (distanciaEuclidea(nave.pos.posicion, glm::vec3{0, 0, 0}) >=
            RADIO_ESFERA_JUGABLE - DISTANCIA_RENDER_PELIGRO) {
            for (Asteroide3D &asteroide : asteroides) {
                asteroide.dibujarSiCercaAntipoda(nave.pos.posicion, DISTANCIA_RENDER_PELIGRO, ventana, camara);
            }
        }
        espacio.dibujar(ventana, camara);
        mallaLimites.dibujar(ventana, camara);

        nave.dibujar(ventana, camara, camaraPrimeraPersona);
        ovni.dibujar(ventana, camara);

        if (camaraPrimeraPersona) {
            dibujaCruz(ventana.getSize());
        }
        // Muestra el fotograma
        ventana.display();
    }
    ventana.setMouseCursorVisible(true);
    ventana.setMouseCursorGrabbed(false);

    // Activa test de profundidad para ocluir triangulos que se encuentran detrás de otros.
    glDisable(GL_DEPTH_TEST);
    ventana.popGLStates();
    return GAME_OVER;
}