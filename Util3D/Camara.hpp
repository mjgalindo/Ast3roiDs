#ifndef AST3ROIDS_CAMARA_HPP_HPP
#define AST3ROIDS_CAMARA_HPP_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <SFML/Graphics.hpp>

struct Camara
{
public:
    Camara(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
    {
        this->pos = pos;
        this->forward = FORWARD_BASE;
        this->up = glm::vec3(0.0f, 1.0f, 0.0f);
        this->projection = glm::perspective(fov, aspect, zNear, zFar);
    }

    inline glm::mat4 proyeccion() const
    {
        return projection * glm::lookAt(pos, pos + forward, up);
    }

    void actualizar(glm::vec2 avanceCursor) {
        glm::quat cuaternioGirar = glm::angleAxis(-avanceCursor.x * 0.005f, up);
        glm::quat cuaternioInclinar = glm::angleAxis(-avanceCursor.y * 0.005f, glm::cross(up, forward));
        auto transformacion = glm::toMat4(cuaternioGirar) * glm::toMat4(cuaternioInclinar);
        up = glm::vec3{transformacion * glm::vec4{up.x, up.y, up.z, 0.0f}};
        forward = glm::vec3{transformacion * glm::vec4{forward.x, forward.y, forward.z, 0.0f}};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            pos = pos + forward * 0.5f;
        }
    }

    glm::mat4 projection;
    glm::vec3 pos;
    glm::vec3 forward;
    glm::vec3 up;

    static constexpr glm::vec3 UP_BASE = {0.0f, 1.0f, 0.0f};
    static constexpr glm::vec3 FORWARD_BASE = {0.0f, 0.0f, 1.0f};
};
#endif //AST3ROIDS_CAMARA_HPP_HPP
