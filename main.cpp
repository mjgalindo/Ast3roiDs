#include <SFML/Graphics.hpp>
#include <memory>
#include <thread>
#include <iostream>
#include <fstream>

#include <SFML/OpenGL.hpp>
#include "Graficos/Nave.hpp"
#include "Graficos/Ovni.hpp"

#define MAX_PUNTS 10

using namespace std;

enum Estado {
    TITULO, MENU, JUEGO, GAME_OVER, PUNTUACIONES, OPCIONES, EXIT
};

Estado tratarTitulo(Estado estado);

Estado tratarMenu(Estado estado);

Estado tratarJuego(Estado estado);

Estado tratarGameOver(Estado estado);

Estado tratarPuntuaciones(Estado estado);

Estado tratarOpciones(Estado estado);

//Tamaño de la ventana
sf::Vector2u resolucion = 2u * RESOLUCION_BASE;

double ratio_alto = 1.0 / RESOLUCION_BASE.x;
double ratio_ancho = 1.0 / RESOLUCION_BASE.y;

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


int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    ventana.create(sf::VideoMode(resolucion.x, resolucion.y), "Ast3roiDs", sf::Style::Default, settings);

    ventana.setFramerateLimit(60);
    ventana.setKeyRepeatEnabled(false);
    ventana.setVerticalSyncEnabled(true);

    Estado estado_actual = TITULO;
    while (ventana.isOpen()) {
        switch (estado_actual) {
            case TITULO:
                estado_actual = tratarTitulo(estado_actual);
                break;
            case MENU:
                estado_actual = tratarMenu(estado_actual);
                break;
            case JUEGO:
                estado_actual = tratarJuego(estado_actual);
                break;
            case GAME_OVER:
                estado_actual = tratarGameOver(estado_actual);
                break;
            case PUNTUACIONES:
                estado_actual = tratarPuntuaciones(estado_actual);
                break;
            case OPCIONES:
                estado_actual = tratarOpciones(estado_actual);
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

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/atari.ttf");

    titulo.setFont(fuente);
    titulo.setString("AST3ROIDS");
    titulo.setCharacterSize(ajustar_h(100u));
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition((resolucion.x - titulo.getLocalBounds().width) / 2, resolucion.y / 5);

    instrucciones.setFont(fuente);
    instrucciones.setString("<ENTER> PARA MENU");
    instrucciones.setCharacterSize(ajustar_h(30u));
    instrucciones.setPosition((resolucion.x - instrucciones.getLocalBounds().width) / 2, ajustar_h(360));
    instrucciones.setFillColor(sf::Color::White);

    sf::Clock reloj;
    bool dibujaInstrucciones = true;

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
        ventana.draw(titulo);
        if (reloj.getElapsedTime().asMilliseconds() > 1000) {
            dibujaInstrucciones = !dibujaInstrucciones;
            reloj.restart();
        }
        if (dibujaInstrucciones)
            ventana.draw(instrucciones);
        ventana.display();
    }
}

Estado tratarMenu(Estado estado) {
    sf::Text texto;
    sf::Text opcion1;
    sf::Text opcion2;
    sf::Text opcion3;
    sf::Text opcion4;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/atari.ttf");

    texto.setFont(fuente);
    texto.setString("MENU");
    texto.setCharacterSize(ajustar_h(80u));
    texto.setPosition({(resolucion.x - texto.getLocalBounds().width) / 2.0f, resolucion.y / 10.0f});
    texto.setFillColor(sf::Color::White);

    opcion1.setFont(fuente);
    opcion1.setString("JUGAR");
    opcion1.setCharacterSize(ajustar_h(40u));
    opcion1.setPosition(
            {(resolucion.x - opcion1.getLocalBounds().width) / 2.0f, resolucion.y / 8 + resolucion.y / 5.0f});
    opcion1.setFillColor(sf::Color::White);

    opcion2.setFont(fuente);
    opcion2.setString("PUNTUACIONES");
    opcion2.setCharacterSize(ajustar_h(40u));
    opcion2.setPosition(
            {(resolucion.x - opcion2.getLocalBounds().width) / 2.0f, resolucion.y / 8 + 2 * resolucion.y / 5.0f});
    opcion2.setFillColor(sf::Color::White);

    opcion3.setFont(fuente);
    opcion3.setString("OPCIONES");
    opcion3.setCharacterSize(ajustar_h(40u));
    opcion3.setPosition(
            {(resolucion.x - opcion3.getLocalBounds().width) / 2, resolucion.y / 8.0f + 3 * resolucion.y / 5.0f});
    opcion3.setFillColor(sf::Color::White);

    opcion4.setFont(fuente);
    opcion4.setString("SALIR");
    opcion4.setCharacterSize(ajustar_h(40u));
    opcion4.setPosition(
            {(resolucion.x - opcion4.getLocalBounds().width) / 2, resolucion.y / 8.0f + 4 * resolucion.y / 5.0f});
    opcion4.setFillColor(sf::Color::White);

    array<Estado, 4> opciones = {JUEGO, PUNTUACIONES, OPCIONES, EXIT};
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
                        seleccion = (seleccion - 1) % (unsigned int) opciones.size();
                    } else if (event.key.code == sf::Keyboard::Down) {
                        seleccion = (seleccion + 1) % (unsigned int) opciones.size();
                    }
                default:
                    break;
            }

            sf::RectangleShape indicador({resolucion.x / 15.0f, resolucion.x / 15.0f});
            switch (seleccion) {
                case 0:
                    indicador.setPosition({opcion1.getPosition().x - resolucion.x / 10, opcion1.getPosition().y});
                    break;
                case 1:
                    indicador.setPosition({opcion2.getPosition().x - resolucion.x / 10, opcion2.getPosition().y});
                    break;
                case 2:
                    indicador.setPosition({opcion3.getPosition().x - resolucion.x / 10, opcion3.getPosition().y});
                    break;
                case 3:
                    indicador.setPosition({opcion4.getPosition().x - resolucion.x / 10, opcion4.getPosition().y});
                    break;
                default:
                    break;
            }

            ventana.clear(sf::Color::Black);
            ventana.draw(indicador);
            ventana.draw(texto);
            ventana.draw(opcion1);
            ventana.draw(opcion2);
            ventana.draw(opcion3);
            ventana.draw(opcion4);
            ventana.display();
        }
    }
}

/// Ejemplo de como reproducir musica. Probablemente queramos
/// desactivarlo con una tecla de mute por lo que hará falta
/// más comunicación con el thread del juego. Además, cada vez
/// debería ser más rapido dependiendo de la puntuación o del
/// avance en cada nivel.
void reproducirMusica(std::shared_ptr<bool> jugando, std::shared_ptr<bool> silencio, std::shared_ptr<bool> reiniciar) {
    sf::SoundBuffer sonido1, sonido2;
    sonido1.loadFromFile("Recursos/Sonido/beat1.wav");
    sonido2.loadFromFile("Recursos/Sonido/beat2.wav");
    sf::Sound reproductor1, reproductor2;
    reproductor1.setBuffer(sonido1);
    reproductor2.setBuffer(sonido2);
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
    for (int i = 0; i < asteroides.size(); i++) {
        if (asteroides[i].estado == DESTRUIDO) {
            asteroides.erase(asteroides.begin() + i);
        }
    }

}

void comprobarMuerteOvni(Ovni ovni) {
    if (ovni.estado == MUERTO) {
        //ovni.erase(asteroides.begin() + i);
    }


}

Estado tratarJuego(Estado estado) {
    puntuacion = 0;

    sf::Text texto;
    sf::Text opcion1;
    sf::Text punt;
    sf::Text vidas;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/atari.ttf");

    punt.setFont(fuente);
    punt.setCharacterSize(ajustar_h(30u));
    punt.setPosition({ajustar_w(20.0f), ajustar_h(10.0f)});
    punt.setFillColor(sf::Color::White);

    vidas.setFont(fuente);
    vidas.setCharacterSize(ajustar_h(30u));
    vidas.setPosition({ajustar_w(20.0f), ajustar_h(45.0f)});
    vidas.setFillColor(sf::Color::White);

    shared_ptr<bool> jugando(new bool(true));
    shared_ptr<bool> silencioMusica(new bool(false));
    shared_ptr<bool> reiniciarMusica(new bool(false));

    thread musica(&reproducirMusica, jugando, silencioMusica, reiniciarMusica);
    sf::Clock reloj;
    int nivel = 0;

    Nave nave = Nave({resolucion.x / 2.0f, resolucion.y / 2.0f}, resolucion, &puntuacion);
    Ovni ovni(resolucion);

    vector<Asteroide> asteroides;
    unsigned int numeroDeAsteroides = 4;
    Asteroide::nuevosAsteroidesAleatorios(asteroides, numeroDeAsteroides, resolucion);

    while (true) {
        if (nave.getVidas() < 0) {
            *jugando = false;
            *silencioMusica = true;
            musica.join();
            return GAME_OVER;
        }

        if (asteroides.size() == 0) {
            nivel++;
            numeroDeAsteroides += 2;
            Asteroide::nuevosAsteroidesAleatorios(asteroides, numeroDeAsteroides, resolucion);
            *reiniciarMusica = true;
        }

        sf::Event event;
        ventana.pollEvent(event);
        switch (event.type) {
            case sf::Event::Closed:
                ventana.close();
                *jugando = false;
                *silencioMusica = true;
                musica.join();
                return EXIT;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::D) {
                    nave.disparar();
                } else if (event.key.code == sf::Keyboard::M) {
                    (*silencioMusica) = !*silencioMusica;
                }
            default:
                break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            nave.rotarIzda();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            nave.rotarDcha();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            nave.acelerar();
        }

        ovni.mover(asteroides, nave);
        nave.mover(asteroides, ovni);
        nave.frenar();

        comprobarMuerteAsteroides(asteroides);
        comprobarMuerteOvni(ovni);
        punt.setString(std::to_string(puntuacion));
        punt.setString(std::to_string(puntuacion));
        vidas.setString(std::to_string(nave.getVidas()));

        ventana.clear(sf::Color::Black);
        ventana.draw(texto);
        ventana.draw(opcion1);
        ventana.draw(punt);
        ventana.draw(vidas);
        ventana.draw(nave);
        ventana.draw(ovni);

        for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
            ast->mover();
            ventana.draw(*ast);
        }

        ventana.display();
        reloj.restart();
        nave.cambiarEstado(nave.getEstado());
        ovni.cambiarEstado(ovni.getEstado());
    }
}

Estado tratarGameOver(Estado estado) {
    sf::Text texto;
    sf::Text opcion1;
    sf::Text Snombre;
    sf::Text nombre;
    sf::Text Spuntuacion;
    sf::Text punt;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/atari.ttf");

    texto.setFont(fuente);
    texto.setString("GAME OVER");
    texto.setCharacterSize(75);
    texto.setPosition({(resolucion.x - texto.getLocalBounds().width) / 2.0f, resolucion.y / 14.0f});
    texto.setFillColor(sf::Color::White);
    texto.setOutlineColor(sf::Color::White);
    texto.setOutlineThickness(1.5);

    opcion1.setFont(fuente);
    opcion1.setString("ACEPTAR");
    opcion1.setCharacterSize(ajustar_h(40u));
    opcion1.setPosition(sf::Vector2f(resolucion.x - opcion1.getLocalBounds().width - 5,
                                     resolucion.y - opcion1.getLocalBounds().height - 5));

    opcion1.setFillColor(sf::Color::White);
    opcion1.setOutlineColor(sf::Color::White);
    opcion1.setOutlineThickness(1.5);

    float altura = resolucion.y / 3.0f;

    Snombre.setFont(fuente);
    Snombre.setString("Nombre del piloto (3 letras): ");
    Snombre.setCharacterSize(30);
    Snombre.setPosition(sf::Vector2f((resolucion.x - Snombre.getLocalBounds().width) / 2.0f, altura));
    Snombre.setFillColor(sf::Color::White);

    string nombre_introducido = "AAA";

    altura += Snombre.getLocalBounds().height + 10;
    nombre.setFont(fuente);
    nombre.setString(nombre_introducido);
    nombre.setCharacterSize(30);
    nombre.setPosition(sf::Vector2f((resolucion.x - nombre.getLocalBounds().width) / 2.0f, altura));
    nombre.setFillColor(sf::Color::White);

    altura += nombre.getLocalBounds().height + 30;
    Spuntuacion.setFont(fuente);
    Spuntuacion.setString("Puntuacion obtenida: ");
    Spuntuacion.setCharacterSize(30);
    Spuntuacion.setPosition(sf::Vector2f((resolucion.x - Spuntuacion.getLocalBounds().width) / 2.0f, altura + 10));
    Spuntuacion.setFillColor(sf::Color::White);

    altura += Spuntuacion.getLocalBounds().height + 10;
    punt.setFont(fuente);
    punt.setString(to_string(puntuacion));
    punt.setCharacterSize(30);
    punt.setPosition(sf::Vector2f((resolucion.x - punt.getLocalBounds().width) / 2.0f, altura + 10));
    punt.setFillColor(sf::Color::White);

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return EXIT;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Return) {
                        ifstream f_puntuaciones("puntuaciones.dat");
                        vector<string> nombres(0);
                        vector<long int> punts(0);
                        if (f_puntuaciones.good()) {
                            string nombre_aux;
                            long int puntuacion_aux;
                            for (int i = 0; i < MAX_PUNTS && !f_puntuaciones.eof(); i++) {
                                f_puntuaciones >> nombre_aux;
                                f_puntuaciones >> puntuacion_aux;

                                if (nombre_aux.compare("") != 0) {
                                    nombres.push_back(nombre_aux);
                                    punts.push_back(puntuacion_aux);
                                }
                            }

                            nombre_aux = nombre_introducido;
                            puntuacion_aux = puntuacion;
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
                        f_puntuaciones.close();

                        ofstream f_puntuaciones_out("puntuaciones.dat");
                        if (f_puntuaciones_out.good()) {
                            for (int i = 0; i < nombres.size(); i++) {
                                f_puntuaciones_out << nombres[i] << " " << punts[i] << endl;
                            }

                            f_puntuaciones_out.flush();
                            f_puntuaciones_out.close();
                        }
                        return PUNTUACIONES;
                    }
                default:
                    break;
            }

            ventana.clear(sf::Color::Black);
            ventana.draw(texto);
            ventana.draw(opcion1);
            ventana.draw(Snombre);
            ventana.draw(nombre);
            ventana.draw(Spuntuacion);
            ventana.draw(punt);
            ventana.display();
        }
    }
}

Estado tratarPuntuaciones(Estado estado) {
    sf::Text texto;
    sf::Text opcion1;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/atari.ttf");

    vector<sf::Text> punts(MAX_PUNTS);

    ifstream f_puntuaciones("puntuaciones.dat");
    if (f_puntuaciones.good()) {
        string nombre;
        long int puntuacion;
        for (int i = 0; i < MAX_PUNTS && !f_puntuaciones.eof(); i++) {
            f_puntuaciones >> nombre;
            f_puntuaciones >> puntuacion;

            string linea = "";
            linea.append(nombre);
            linea.append("    ");
            linea.append(to_string(puntuacion));

            sf::Text punt;
            punt.setFont(fuente);
            punt.setCharacterSize(30);
            punt.setString(linea);
            punt.setPosition({(resolucion.x - punt.getLocalBounds().width) / 2.0f,
                              resolucion.y / 3.5f + i * resolucion.y / 14.0f});
            punt.setFillColor(sf::Color::White);

            punts.push_back(punt);
        }
    }
    f_puntuaciones.close();

    texto.setFont(fuente);
    texto.setString("PUNTUACIONES");
    texto.setCharacterSize(ajustar_h(75u));
    texto.setPosition({(resolucion.x - texto.getLocalBounds().width) / 2.0f, resolucion.y / 14.0f});
    texto.setFillColor(sf::Color::White);
    texto.setOutlineColor(sf::Color::White);
    texto.setOutlineThickness(1.5);

    opcion1.setFont(fuente);
    opcion1.setString("ACEPTAR");
    opcion1.setCharacterSize(ajustar_h(40u));
    opcion1.setPosition(sf::Vector2f(resolucion.x - opcion1.getLocalBounds().width - 5,
                                     resolucion.y - opcion1.getLocalBounds().height - 5));

    opcion1.setFillColor(sf::Color::White);
    opcion1.setOutlineColor(sf::Color::White);
    opcion1.setOutlineThickness(1.5);


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

            ventana.clear(sf::Color::Black);
            ventana.draw(texto);
            ventana.draw(opcion1);

            for (unsigned int i = 0; i < punts.size(); i++) {
                ventana.draw(punts[i]);
            }

            ventana.display();
        }
    }
}

Estado tratarOpciones(Estado estado) {
    sf::Text texto;
    sf::Text opcion1;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/atari.ttf");

    texto.setFont(fuente);
    texto.setString("OPCIONES");
    texto.setCharacterSize(ajustar_h(30u));
    texto.setFillColor(sf::Color::White);

    opcion1.setFont(fuente);
    opcion1.setString("1-MENU");
    opcion1.setCharacterSize(ajustar_h(30u));
    opcion1.setPosition({ajustar_w(0.0f), ajustar_h(35.0f)});
    opcion1.setFillColor(sf::Color::White);

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return EXIT;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Num1) {
                        return MENU;
                    }
                default:
                    break;
            }

            ventana.clear(sf::Color::Black);
            ventana.draw(texto);
            ventana.draw(opcion1);
            ventana.display();
        }
    }
}
