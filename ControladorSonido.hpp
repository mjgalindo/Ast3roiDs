#ifndef AST3ROIDS_CONTROLADORSONIDO_HPP
#define AST3ROIDS_CONTROLADORSONIDO_HPP

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <array>
#include <unordered_map>

class ControladorSonido {
public:
    enum Sonido {
        EXP_0 = 0, EXP_1, EXP_2, ACELERAR, DISPARO, VIDA_EXTRA, OVNI_PEQUENO, OVNI_GRANDE, HAS_MUERTO, TELETRANSPORTE, NUM_SONIDOS
    };
private:
    std::array<sf::SoundBuffer, NUM_SONIDOS> buffers;
    std::array<sf::Sound, NUM_SONIDOS> reproductores;

    float volumenBase;

public:

    ControladorSonido(float volumen = 80.0f);

    /**
     * Devuelve el buffer del sonido elegido
     */
    sf::SoundBuffer buffer(Sonido sonido);

    void reproducir(Sonido sonido, bool acumular = false);

    void detener(Sonido sonido);

    void setVolumen(float nuevoVolumen);
};


#endif //AST3ROIDS_CONTROLADORSONIDO_HPP
