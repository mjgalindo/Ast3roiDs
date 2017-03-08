#include <SFML/Graphics.hpp>
#include <memory>
#include <thread>
#include <iostream>

#include "Graficos/Nave.hpp"
#include "Graficos/Asteroide.hpp"
#include "Graficos/Ovni.hpp"

using namespace std;

enum Estado {
    TITULO, MENU, JUEGO, GAME_OVER, PUNTUACIONES, OPCIONES, ERROR
};

Estado tratarTitulo(Estado estado);
Estado tratarMenu(Estado estado);
Estado tratarJuego(Estado estado);
Estado tratarGameOver(Estado estado);
Estado tratarPuntuaciones(Estado estado);
Estado tratarOpciones(Estado estado);

//Tamaño de la ventana
sf::Vector2u MAX_SIZE = {800,600};
//Ventana
sf::RenderWindow ventana;

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    ventana.create(sf::VideoMode(MAX_SIZE.x,MAX_SIZE.y), "Ast3roiDs", sf::Style::Default, settings);

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
    titulo.setCharacterSize(MAX_SIZE.y / 6);
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition((MAX_SIZE.x - titulo.getLocalBounds().width) / 2, MAX_SIZE.y / 5);

    instrucciones.setFont(fuente);
    instrucciones.setString("<ENTER> PARA MENU");
    instrucciones.setCharacterSize(MAX_SIZE.y / 20);
    instrucciones.setPosition((MAX_SIZE.x - instrucciones.getLocalBounds().width) / 2, 3 * MAX_SIZE.y / 5);
    instrucciones.setFillColor(sf::Color::White);

    sf::Clock reloj;
    bool dibujaInstrucciones = true;

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return ERROR;
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
    texto.setCharacterSize(80);
    texto.setPosition({(MAX_SIZE.x - texto.getLocalBounds().width) / 2.0f, MAX_SIZE.y / 10.0f});
    texto.setFillColor(sf::Color::White);

    opcion1.setFont(fuente);
    opcion1.setString("1-JUEGO");
    opcion1.setCharacterSize(40);
    opcion1.setPosition({(MAX_SIZE.x - opcion1.getLocalBounds().width) / 2.0f, MAX_SIZE.y / 8 + MAX_SIZE.y / 5.0f});
    opcion1.setFillColor(sf::Color::White);

    opcion2.setFont(fuente);
    opcion2.setString("2-PUNTUACIONES");
    opcion2.setCharacterSize(40);
    opcion2.setPosition({(MAX_SIZE.x - opcion2.getLocalBounds().width) / 2.0f, MAX_SIZE.y / 8 + 2 * MAX_SIZE.y / 5.0f});
    opcion2.setFillColor(sf::Color::White);

    opcion3.setFont(fuente);
    opcion3.setString("3-OPCIONES");
    opcion3.setCharacterSize(40);
    opcion3.setPosition({(MAX_SIZE.x - opcion3.getLocalBounds().width) / 2, MAX_SIZE.y / 8.0f + 3 * MAX_SIZE.y / 5.0f});
    opcion3.setFillColor(sf::Color::White);

    opcion4.setFont(fuente);
    opcion4.setString("4-SALIR");
    opcion4.setCharacterSize(40);
    opcion4.setPosition({(MAX_SIZE.x - opcion4.getLocalBounds().width) / 2, MAX_SIZE.y / 8.0f + 4 * MAX_SIZE.y / 5.0f});
    opcion4.setFillColor(sf::Color::White);

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return ERROR;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Num1) {
                        return JUEGO;
                    } else if (event.key.code == sf::Keyboard::Num2) {
                        return PUNTUACIONES;
                    } else if (event.key.code == sf::Keyboard::Num3) {
                        return OPCIONES;
                    } else if (event.key.code == sf::Keyboard::Num4) {
                        return ERROR;
                    }
                default:
                    break;
            }

            ventana.clear(sf::Color::Black);
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
void reproducirMusica(std::shared_ptr<bool> jugando) {
    sf::SoundBuffer sonido1, sonido2;
    sonido1.loadFromFile("Recursos/Sonido/beat1.wav");
    sonido2.loadFromFile("Recursos/Sonido/beat2.wav");
    sf::Sound reproductor1, reproductor2;
    reproductor1.setBuffer(sonido1);
    reproductor2.setBuffer(sonido2);
    int tiempoEntreSonidos = 1000;
    while (*jugando) {
        reproductor1.play();
        sf::sleep(sf::milliseconds(tiempoEntreSonidos));
        reproductor2.play();
        sf::sleep(sf::milliseconds(tiempoEntreSonidos));
        if (tiempoEntreSonidos > 200)
            tiempoEntreSonidos -= 10;
    }
}

Estado tratarJuego(Estado estado) {
    sf::Text texto;
    sf::Text opcion1;
    sf::Text puntuacion;
    sf::Text vidas;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/atari.ttf");

    puntuacion.setFont(fuente);
    puntuacion.setCharacterSize(30);
    puntuacion.setPosition(sf::Vector2f(0.0, 0.0));
    puntuacion.setFillColor(sf::Color::Blue);

    vidas.setFont(fuente);
    vidas.setCharacterSize(30);
    vidas.setPosition(sf::Vector2f(0.0, 35.0));
    vidas.setFillColor(sf::Color::Blue);

    Nave nave = Nave(sf::Vector2f(MAX_SIZE.x / 2.0f, MAX_SIZE.y / 2.0f));
    Ovni ovni = Ovni(MAX_SIZE);

    /// A modo demo, no tiene sentido que esto esté aqui, deberá ser aleatorio etc
    vector<Asteroide> asteroides{
            Asteroide({120, 10}, 0.4, {0.1, 0.1}, TIPO_0, TAM_0),
            Asteroide({10, 400}, 0.4, {-0.1, 0.1}, TIPO_1, TAM_1),
            Asteroide({400, 80}, 0.4, {0.1, -0.1}, TIPO_2, TAM_2),
            //Asteroide({500, 1080}, 0.4, {3.5f, 4.5f}, Asteroide::TIPO_1, 5),
    };

    shared_ptr<bool> jugando(new bool(true));
    thread musica(&reproducirMusica, jugando);
    sf::Clock reloj;
    while (true) {
        sf::Event event;
        ventana.pollEvent(event);
        switch (event.type) {
            case sf::Event::Closed:
                ventana.close();
                *jugando = false;
                musica.join();
                return ERROR;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::D) {
                    nave.disparar();
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

        ovni.mover(MAX_SIZE);
        nave.mover(MAX_SIZE, asteroides);
        nave.frenar();

        if(nave.getVidas()<0){
            *jugando = false;
            musica.join();
            return GAME_OVER;
        }


        puntuacion.setString(std::to_string(nave.getPuntuacion()));
        vidas.setString(std::to_string(nave.getVidas()));

        ventana.clear(sf::Color::Black);
        ventana.draw(texto);
        ventana.draw(opcion1);
        ventana.draw(puntuacion);
        ventana.draw(vidas);
        ventana.draw(nave);
        ventana.draw(ovni);

        for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
            ast->mover(MAX_SIZE);
            ventana.draw(*ast);
        }

        ventana.display();
        reloj.restart();
        nave.comprobarEstado();
    }
}

Estado tratarGameOver(Estado estado) {
    sf::Text texto;
    sf::Text opcion1;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/atari.ttf");

    texto.setFont(fuente);
    texto.setString("GAME OVER");
    texto.setCharacterSize(30);
    texto.setFillColor(sf::Color::White);

    opcion1.setFont(fuente);
    opcion1.setString("1-PUNTUACIONES");
    opcion1.setCharacterSize(30);
    opcion1.setPosition(sf::Vector2f(0.0, 35.0));
    opcion1.setFillColor(sf::Color::White);

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return ERROR;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Num1) {
                        return PUNTUACIONES;
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

Estado tratarPuntuaciones(Estado estado) {
    sf::Text texto;
    sf::Text opcion1;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/atari.ttf");

    texto.setFont(fuente);
    texto.setString("PUNTUACIONES");
    texto.setCharacterSize(30);
    texto.setFillColor(sf::Color::White);

    opcion1.setFont(fuente);
    opcion1.setString("1-MENU");
    opcion1.setCharacterSize(30);
    opcion1.setPosition(sf::Vector2f(0.0, 35.0));
    opcion1.setFillColor(sf::Color::White);

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return ERROR;
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

Estado tratarOpciones(Estado estado) {
    sf::Text texto;
    sf::Text opcion1;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/atari.ttf");

    texto.setFont(fuente);
    texto.setString("OPCIONES");
    texto.setCharacterSize(30);
    texto.setFillColor(sf::Color::White);

    opcion1.setFont(fuente);
    opcion1.setString("1-MENU");
    opcion1.setCharacterSize(30);
    opcion1.setPosition(sf::Vector2f(0.0, 35.0));
    opcion1.setFillColor(sf::Color::White);

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return ERROR;
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
