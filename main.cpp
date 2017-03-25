
#include <glew.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <thread>
#include <iostream>
#include <SFML/OpenGL.hpp>
#include "Graficos/Nave.hpp"
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
    GLfloat points[] = {
            0.0f,  0.5f,  0.0f,
            0.5f,
            -0.5f,  0.0f,
            -  0.5f,
            -0.5f,  0.0f
    };
    GLfloat colors[] = {
            1.0f, 0.0f,
            0.0f,
            0.0f, 1.0f,
            0.0f,
            0.0f, 0.0f,
            1.0f
    };
    /*GLuint points_VBO = 0;
    GLuint colors_VBO = 0;
    glGenBuffers(1, &points_VBO);
    glGenBuffers(1, &colors_VBO);
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, points_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, colors_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),NULL);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    */
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
    opcion1.setString("JUGAR");
    opcion1.setCharacterSize(40);
    opcion1.setPosition({(MAX_SIZE.x - opcion1.getLocalBounds().width) / 2.0f, MAX_SIZE.y / 8 + MAX_SIZE.y / 5.0f});
    opcion1.setFillColor(sf::Color::White);

    opcion2.setFont(fuente);
    opcion2.setString("PUNTUACIONES");
    opcion2.setCharacterSize(40);
    opcion2.setPosition({(MAX_SIZE.x - opcion2.getLocalBounds().width) / 2.0f, MAX_SIZE.y / 8 + 2 * MAX_SIZE.y / 5.0f});
    opcion2.setFillColor(sf::Color::White);

    opcion3.setFont(fuente);
    opcion3.setString("OPCIONES");
    opcion3.setCharacterSize(40);
    opcion3.setPosition({(MAX_SIZE.x - opcion3.getLocalBounds().width) / 2, MAX_SIZE.y / 8.0f + 3 * MAX_SIZE.y / 5.0f});
    opcion3.setFillColor(sf::Color::White);

    opcion4.setFont(fuente);
    opcion4.setString("SALIR");
    opcion4.setCharacterSize(40);
    opcion4.setPosition({(MAX_SIZE.x - opcion4.getLocalBounds().width) / 2, MAX_SIZE.y / 8.0f + 4 * MAX_SIZE.y / 5.0f});
    opcion4.setFillColor(sf::Color::White);

    array<Estado, 4> opciones = {JUEGO, PUNTUACIONES, OPCIONES, ERROR};
    int seleccion = 0;

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return ERROR;
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

            sf::RectangleShape indicador({MAX_SIZE.x / 15.0f, MAX_SIZE.x / 15.0f});
            switch (seleccion) {
                case 0:
                    indicador.setPosition({opcion1.getPosition().x - MAX_SIZE.x / 10, opcion1.getPosition().y});
                    break;
                case 1:
                    indicador.setPosition({opcion2.getPosition().x - MAX_SIZE.x / 10, opcion2.getPosition().y});
                    break;
                case 2:
                    indicador.setPosition({opcion3.getPosition().x - MAX_SIZE.x / 10, opcion3.getPosition().y});
                    break;
                case 3:
                    indicador.setPosition({opcion4.getPosition().x - MAX_SIZE.x / 10, opcion4.getPosition().y});
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
void reproducirMusica(std::shared_ptr<bool> jugando, std::shared_ptr<bool> silencio) {
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
    }
}
void comprobarMuerteAsteroides(std::vector<Asteroide> &asteroides){
    for(int i=0; i<asteroides.size(); i++){
        if(asteroides[i].estado == DESTRUIDO){
            asteroides.erase(asteroides.begin() + i);
        }
    }

}
void comprobarMuerteOvni(Ovni ovni){
    if(ovni.estado == MUERTO){
        //ovni.erase(asteroides.begin() + i);
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
    puntuacion.setFillColor(sf::Color::White);

    vidas.setFont(fuente);
    vidas.setCharacterSize(30);
    vidas.setPosition(sf::Vector2f(0.0, 35.0));
    vidas.setFillColor(sf::Color::White);

    shared_ptr<bool> jugando(new bool(true));
    shared_ptr<bool> silencioMusica(new bool(false));

    thread musica(&reproducirMusica, jugando, silencioMusica);
    sf::Clock reloj;
    int nivel = 0;

    Nave nave = Nave(sf::Vector2f(MAX_SIZE.x / 2.0f, MAX_SIZE.y / 2.0f));
    Ovni ovni;
    vector<Asteroide> asteroides;
    unsigned int numeroDeAsteroides = 4;
    Asteroide::nuevosAsteroidesAleatorios(asteroides, numeroDeAsteroides, MAX_SIZE);

    while (true) {
        if(nave.getVidas()<0){
            *jugando = false;
            musica.join();
            return GAME_OVER;
        }

        if(asteroides.size()==0){
            nivel++;
            numeroDeAsteroides+=2;
            Asteroide::nuevosAsteroidesAleatorios(asteroides, numeroDeAsteroides, MAX_SIZE);
        }

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

        ovni.mover(MAX_SIZE, asteroides, nave);
        nave.mover(MAX_SIZE, asteroides, ovni);
        nave.frenar();

        comprobarMuerteAsteroides(asteroides);
        comprobarMuerteOvni(ovni);
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
        nave.cambiarEstado(nave.getEstado(),MAX_SIZE);
        ovni.cambiarEstado(ovni.getEstado(),MAX_SIZE);
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