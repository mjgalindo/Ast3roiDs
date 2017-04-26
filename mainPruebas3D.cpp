#include <iostream>
#include "Graficos3D/Asteroide3D.hpp"
#include "Graficos3D/Nave3D.hpp"
#include "Graficos3D/Ovni3D.hpp"
#include "Util3D/Ventana3D.hpp"
#include "Util3D/ControladorTexturas.hpp"
#include "Util3D/ControladorShaders.hpp"
#include "Graficos3D/Esfera.hpp"

using namespace std;
using namespace sf;

#define WIDTH 1700
#define HEIGHT 1100

long int puntuacion = 0;

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

sf::Font fuenteAsteroids;/*
inline void inicializaTexto(sf::Text &texto, unsigned int tamanoFuente, double grosorLinea = 0.3) {

    FT_Library ft;

    if(FT_Init_FreeType(&ft)) {
        fprintf(stderr, "Could not init freetype library\n");
        return 1;
    }
    FT_Face face;

    if(FT_New_Face(ft, "Recursos/Fuentes/atari.ttf", 0, &face)) {
        fprintf(stderr, "Could not open font\n");
        return 1;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
}*/
int main() {
    // Configura la ventana
    sf::ContextSettings configuracion;
    configuracion.depthBits = 24;
    configuracion.stencilBits = 8;
    configuracion.antialiasingLevel = 2;
    configuracion.majorVersion = 3;
    configuracion.minorVersion = 3;

    // Crea la ventana. El constructor carga las funciones de OpenGL y llama a glewInit() por lo que esto se debe
    // hacer al principio.
    Ventana3D ventana(sf::VideoMode(WIDTH, HEIGHT), "OpenGL", sf::Style::Close | sf::Style::Titlebar, configuracion,
                      60);
    ventana.setMouseCursorVisible(false);
    ventana.setMouseCursorGrabbed(true);

    // Inicializa los modelos 3D y las texturas. Esto objetos solo existe para controlar
    // la creacion y destrucción de recursos.
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
    const float DISTANCIA_RENDER_PELIGRO = 60.0f;
    Esfera mallaLimites(ControladorTexturas::BLANCO, {0, 0, 0},
                        {RADIO_ESFERA_JUGABLE, RADIO_ESFERA_JUGABLE, RADIO_ESFERA_JUGABLE}, true);

    // Carga asteroides para ver como se mueve la nave
    vector<Asteroide3D> asteroides;
    for (int i = 0; i < 10; i++)
        asteroides.emplace_back(csonido.get(), RADIO_ESFERA_JUGABLE);

    Nave3D nave(csonido.get(), &puntuacion, RADIO_ESFERA_JUGABLE);

    Ovni3D ovni(csonido.get(), RADIO_ESFERA_JUGABLE);

    Camara camara({0.0f, 0.0f, 0.0f}, Ventana3D::FOV, (float) ventana.getSize().x / (float) ventana.getSize().y,
                  Ventana3D::Z_NEAR, Ventana3D::Z_FAR);
    bool camaraPrimeraPersona = false;
    bool running = true;
    int nivel =1;
    while (running) {
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
                    } else if (event.key.code == sf::Keyboard::Key::D) {
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

        nave.actualizar(nivel,asteroides, ovni,
                        {posCursor.x - (int) ventana.getSize().x / 2, posCursor.y - (int) ventana.getSize().y / 2});
        if (ventana.hasFocus())
            sf::Mouse::setPosition({(int) ventana.getSize().x / 2, (int) ventana.getSize().y / 2}, ventana);

        if (nave.getVidas() < 0) {
            running = false;
        }

        ovni.actualizar(nivel,asteroides, nave);

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

        nave.dibujar(ventana, camara);
        ovni.dibujar(ventana, camara);

        if (camaraPrimeraPersona) {
            dibujaCruz(ventana.getSize());
        }
        // Muestra el fotograma
        ventana.display();
    }

    return 0;
}