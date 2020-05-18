#include "Shader.hpp"
#include <iostream>
#include <fstream>

namespace vj {
    Shader::Shader(const std::string &fileName) {
        programa = glCreateProgram();
        shaders[0] = creaShader(cargaFichero(fileName + ".vert"), GL_VERTEX_SHADER);
        shaders[1] = creaShader(cargaFichero(fileName + ".frag"), GL_FRAGMENT_SHADER);

        for (unsigned int i = 0; i < NUM_SHADERS; i++)
            glAttachShader(programa, shaders[i]);


        (programa, 0, "position");
        glBindAttribLocation(programa, 1, "texCoord");
        glBindAttribLocation(programa, 2, "normal");

        glLinkProgram(programa);
        compruebaErrores(programa, GL_LINK_STATUS, true, "Error enlazando el shader");

        glValidateProgram(programa);
        compruebaErrores(programa, GL_LINK_STATUS, true, "Programa no válido");

        m_uniforms[0] = glGetUniformLocation(programa, "MVP");
        m_uniforms[1] = glGetUniformLocation(programa, "Normal");
        m_uniforms[2] = glGetUniformLocation(programa, "lightDirection");
    }

    Shader::~Shader() {
        for (unsigned int i = 0; i < NUM_SHADERS; i++) {
            glDetachShader(programa, shaders[i]);
            glDeleteShader(shaders[i]);
        }
        glDeleteProgram(programa);
    }

    void Shader::bind() {
        glUseProgram(programa);
    }

    void Shader::actualizar(const Posicionamiento &transformacion, const Camara &camara) {
        glm::mat4 MVP = transformacion.modeloVistaProyeccion(camara);
        glm::mat4 Normal = transformacion.matrizModelo();

        glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(m_uniforms[1], 1, GL_FALSE, &Normal[0][0]);
    }

    std::string Shader::cargaFichero(const std::string &nomFichero) {
        std::ifstream fichero;
        fichero.open((nomFichero).c_str());

        std::string retVal;
        std::string linea;

        if (fichero.is_open()) {
            while (fichero.good()) {
                getline(fichero, linea);
                retVal.append(linea + "\n");
            }
        } else {
            std::cerr << "No se puede cargar el shader: " << nomFichero << std::endl;
        }

        return retVal;
    }

    void Shader::compruebaErrores(GLuint shader, GLuint flag, bool programa, const std::string &errorMessage) {
        GLint exito = 0;
        GLchar error[1024] = {0};

        if (programa)
            glGetProgramiv(shader, flag, &exito);
        else
            glGetShaderiv(shader, flag, &exito);

        if (exito == GL_FALSE) {
            if (programa)
                glGetProgramInfoLog(shader, sizeof(error), NULL, error);
            else
                glGetShaderInfoLog(shader, sizeof(error), NULL, error);
            std::cerr << errorMessage << ": '" << error << "'" << std::endl;
        }
    }

    GLuint Shader::creaShader(const std::string &texto, unsigned int tipo) {
        GLuint shader = glCreateShader(tipo);

        if (shader == 0)
            std::cerr << "Error al crear shader con tipo " << tipo << std::endl;

        const GLchar *p[1];
        p[0] = texto.c_str();
        GLint tamanos[1];
        tamanos[0] = (GLint) texto.length();

        glShaderSource(shader, 1, p, tamanos);
        glCompileShader(shader);

        compruebaErrores(shader, GL_COMPILE_STATUS, false, "Error al compilar el shader!");

        return shader;
    }

    void Shader::setDireccionLuz(glm::vec3 direccion) {
        glUniform3f(m_uniforms[2], direccion.x, direccion.y, direccion.z);
    }
}