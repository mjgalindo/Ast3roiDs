#ifndef AST3ROIDS_CAMARA_HPP_HPP
#define AST3ROIDS_CAMARA_HPP_HPP

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camara
{
public:
    Camara(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
    {
        this->pos = pos;
        this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
        this->up = glm::vec3(0.0f, 1.0f, 0.0f);
        this->projection = glm::perspective(fov, aspect, zNear, zFar);
    }

    inline glm::mat4 proyeccion() const
    {
        return projection * glm::lookAt(pos, pos + forward, up);
    }

    glm::mat4 projection;
    glm::vec3 pos;
    glm::vec3 forward;
    glm::vec3 up;
};
#endif //AST3ROIDS_CAMARA_HPP_HPP
