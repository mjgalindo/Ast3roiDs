#ifndef AST3ROIDS_TEXTURA_HPP
#define AST3ROIDS_TEXTURA_HPP

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
namespace vj {
    class Textura {
    public:
        Textura(const std::string &fileName);

        void bind();

        virtual ~Textura();

    protected:
    private:
        // Una copia sería problemática porque llama al destructor invalidando la textura
        Textura(const Textura& copia) = delete;
        GLuint m_texture;
    };
}

#endif //AST3ROIDS_TEXTURA_HPP
