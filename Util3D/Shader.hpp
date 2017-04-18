#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <string>
#include <GL/glew.h>
#include "Transformacion.hpp"
#include <array>

namespace vj {

    class Shader {
    public:
        Shader(const std::string &fileName);

        virtual ~Shader();

        void bind();

        void actualizar(const Transformacion &transformacion, const Camara &camara);

        void setDireccionLuz(glm::vec3 direccion);

    protected:
    private:
        // Una copia sería problemática porque llama al destructor invalidando el shader
        Shader(const Shader &copia) = delete;

        static const unsigned int NUM_SHADERS = 2;
        static const unsigned int NUM_UNIFORMS = 4;

        void operator=(const Shader &shader) = delete;

        std::string cargaFichero(const std::string &nomFichero);

        void compruebaErrores(GLuint shader, GLuint flag, bool programa, const std::string &errorMessage);

        GLuint creaShader(const std::string &texto, unsigned int tipo);

        GLuint programa;
        std::array<GLuint, NUM_SHADERS> shaders;
        std::array<GLint, NUM_UNIFORMS> m_uniforms;
    };
}
#endif
