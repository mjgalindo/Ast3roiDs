#include "ControladorSonido.hpp"

ControladorSonido::ControladorSonido(float volumen) {
    volumenBase = volumen;
    if (!buffers[EXP_0].loadFromFile("Recursos/Sonido/bangSmall.wav")) {
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/bangSmall.wav\"");
    }
    if (!buffers[EXP_1].loadFromFile("Recursos/Sonido/bangMedium.wav")) {
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/bangMedium.wav\"");
    }
    if (!buffers[EXP_2].loadFromFile("Recursos/Sonido/bangLarge.wav")) {
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/bangLarge.wav\"");
    }
    if (!buffers[ACELERAR].loadFromFile("Recursos/Sonido/thrust.wav")) {
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/thrust.wav\"");
    }
    if (!buffers[DISPARO].loadFromFile("Recursos/Sonido/fire.wav")) {
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/fire.wav\"");
    }
    if (!buffers[VIDA_EXTRA].loadFromFile("Recursos/Sonido/extraShip.wav")) {
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/extraShip.wav\"");
    }
    if (!buffers[OVNI_PEQUENO].loadFromFile("Recursos/Sonido/saucerSmall.wav")) {
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/saucerSmall.wav\"");
    }
    if (!buffers[OVNI_GRANDE].loadFromFile("Recursos/Sonido/saucerBig.wav")) {
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/saucerBig.wav\"");
    }

    for (int i = 0; i < NUM_SONIDOS; i++) {
        reproductores[i].setBuffer(buffers[i]);
        reproductores[i].setVolume(volumenBase);
    }
    reproductores[ACELERAR].setVolume(volumenBase * 1.4f);
    reproductores[OVNI_PEQUENO].setLoop(true);
    reproductores[OVNI_GRANDE].setLoop(true);
}

sf::SoundBuffer ControladorSonido::buffer(Sonido sonido) {
    return sf::SoundBuffer(buffers[sonido]);
}

void ControladorSonido::reproducir(Sonido sonido, bool acumular) {
    if (acumular || reproductores[sonido].getStatus() == sf::Sound::Status::Stopped)
        reproductores[sonido].play();
}

void ControladorSonido::detener(Sonido sonido) {
    reproductores[sonido].stop();
}

void ControladorSonido::setVolumen(float nuevoVolumen) {
    volumenBase = nuevoVolumen;
    for (int i = 0; i < NUM_SONIDOS; i++) {
        reproductores[i].setVolume(volumenBase);
    }
    reproductores[ACELERAR].setVolume(volumenBase * 1.5f);
}