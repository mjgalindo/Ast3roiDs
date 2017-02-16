#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main() {

    Vector2u MAX_SIZE;

    // Creacion de la ventana
    RenderWindow window;

    for(VideoMode vm : VideoMode::getFullscreenModes()) {
        if(vm.isValid()) {
            window.create(VideoMode::getDesktopMode(), "My window", Style::Fullscreen);
            MAX_SIZE = window.getSize();
            break;
        }
    }

    Vector2f posicion;
    posicion.x = window.getSize().x / 2;
    posicion.y = window.getSize().y / 2;

    CircleShape circulo(10);
    circulo.setPosition(posicion);
    circulo.setFillColor(sf::Color(255, 255, 255));

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {

            switch(event.type){
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    if(Keyboard::isKeyPressed(Keyboard::Left)){
                        posicion.x -= 2;
                        if(posicion.x<0){
                            posicion.x = MAX_SIZE.x;
                        }
                        circulo.setPosition(posicion);
                    }
                    else if(Keyboard::isKeyPressed(Keyboard::Right)){
                        posicion.x += 2;
                        if(posicion.x>MAX_SIZE.x){
                            posicion.x = 0;
                        }
                        circulo.setPosition(posicion);
                    }
                    else if(Keyboard::isKeyPressed(Keyboard::Up)){
                        posicion.y -= 2;
                        if(posicion.y<0){
                            posicion.y = MAX_SIZE.y;
                        }
                        circulo.setPosition(posicion);
                    }
                    else if(Keyboard::isKeyPressed(Keyboard::Down)){
                        posicion.y += 2;
                        if(posicion.y>MAX_SIZE.y){
                            posicion.y = 0;
                        }
                        circulo.setPosition(posicion);
                    }
                    else if(Keyboard::isKeyPressed(Keyboard::Escape)){
                        window.close();
                    }
            }
        }

        // Se borra la pantalla con negro
        window.clear(Color::Black);

        //Se dibuja el circulo
        window.draw(circulo);

        // Se muestra la ventana
        window.display();
    }

    return 0;
}
